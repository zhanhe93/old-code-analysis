// FileRead.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOOLEAN int
#define TRUE 1
#define FALSE 0

int readLn(FILE * fp, char * ln)
{
	int c, ret;
	ret = 0;char * first = ln;
	while (1)
	{
		c = fgetc(fp);
		if (c == EOF)
		{
			*ln = 0;
			return ret;
		}
		*ln = (char)c;
		ln++;
		ret++;

		if (c == '\n')
		{
			if ((first < (ln -1)) && (*(ln - 2) == '\r'))
			{   
				*(ln - 2) = 0;
				ret--;
			}
			else
				*(ln - 1) = 0;
			ret--;
			return ret;
		}
	}
	return ret;
}



typedef void (*TCloseTextFile)();
typedef BOOLEAN (*TOpenTextFile)();
typedef BOOLEAN (*TReadLine)(char * Ln);
typedef void (*TWriteLine)(char * Ln);


struct TTextFileInfo{
	FILE * F;
	char FileName[256];
	int CurrentLine;
	int TotalLine;
	char* Mode;//the open mode of the file
    TOpenTextFile Open;
	TCloseTextFile Close;
	TReadLine ReadLn;
    TWriteLine WriteLn;
};

typedef TTextFileInfo * PTextFileInfo ;

void usage()
{
	printf("please input file path like this: fileread c:\temp \n");
}

int GetLineCount(char *FileName)
{
  FILE * f;
  char Ln[256];
  int cnt = 0;
  f = fopen(FileName, "r");  
  if (f == NULL)
  {
	  return 0;
  }
  
  while (! feof(f))
  {
	  readLn(f, Ln);
      cnt++;
  }
  fclose(f);   
  return cnt;
}

void fatalErr(char * msg)
{
	printf("%s\n", msg);
	exit(1);
}

BOOLEAN OpenTextFile()
{	
	PTextFileInfo pInfo;
	_asm
	{
		mov pInfo, edx;
	}
	if (0 == strcmp(pInfo->Mode, "r"))
	{
		pInfo->TotalLine = GetLineCount(pInfo->FileName);
		pInfo->CurrentLine = 0;
	}
	else if (0 == strcmp(pInfo->Mode, "w"))
	{
		pInfo->TotalLine = 0;
		pInfo->CurrentLine = 0;
	}
	else if (0 == strcmp(pInfo->Mode, "w+"))
	{
		pInfo->CurrentLine = GetLineCount(pInfo->FileName);
		pInfo->TotalLine = pInfo->CurrentLine;		
	}
	else
	{
		fatalErr("just support r, w, and w+");
	}
	pInfo->F = fopen(pInfo->FileName, pInfo->Mode);		

	return pInfo->F == NULL ? FALSE : TRUE;
}

BOOLEAN ReadLine(char *Ln)
{
	PTextFileInfo pInfo;
	_asm
	{
		mov pInfo, edx;
	}
	if (feof(pInfo->F))
      return FALSE;
    readLn(pInfo->F, Ln);
	pInfo->CurrentLine++;
	return TRUE;
}

void WriteLine(char * Ln)
{
	PTextFileInfo pInfo;
	_asm
	{
		mov pInfo, edx;
	}
	fwrite(Ln, strlen(Ln), 1, pInfo->F);
	fwrite("\r\n", 2, 1, pInfo->F);
	pInfo->CurrentLine++;
	pInfo->TotalLine = pInfo->CurrentLine;
}

void CloseTextFile()
{
	PTextFileInfo pInfo;
	_asm
	{
		mov pInfo, edx;
	}
	fclose(pInfo->F);
}

void InitTextFileInfo(PTextFileInfo pInfo)
{
	pInfo->Open = OpenTextFile;
	pInfo->Close = CloseTextFile;
	pInfo->ReadLn = ReadLine;
	pInfo->WriteLn = WriteLine;
}

void InitTextFileInfo2(PTextFileInfo pInfo, char * FileName, char * Mode)
{
	InitTextFileInfo(pInfo);
	strcpy(pInfo->FileName, FileName);
	pInfo->Mode = Mode;
}


void main(int argc, char* argv[])
{
	if (argc != 2)
	{
		usage();
		return;
	}
	TTextFileInfo info;
	InitTextFileInfo2(&info, argv[1], "r");	
	void * self = &info;
	_asm
	{
		mov edx, self;
	}
	if (FALSE == info.Open ())
	{
		printf("cannot open file %s\n", argv[1]);
		return;
	}
    char Ln[512];
	while (1)
	{
		_asm
		{
			mov edx, self;
		}
		if (TRUE == info.ReadLn(Ln))
			printf("%s \n", Ln);
		else
			break;
	}
	_asm
	{
		mov edx, self;
	}
	info.Close();
	printf("----------------- file: %s -----------------\n", info.FileName);
	printf("----------------- total line count=%d -----------------\n", info.TotalLine);
	getchar();
}

