#ifndef LINKER_XXXX 
#define LINKER_XXXX 

#define COFF_SYMBOL_TYPE_FUNC 0x20

#define COFF_BSS_TYPE 0x00000080

#define IMAGE_SYM_CLASS_EXTERNAL 0x02

#define IMAGE_REL_I386_DIR32 0x0006
#define IMAGE_REL_I386_REL32 0x0014

#define IMAGE_SCN_CNT_CODE 0X20

#pragma pack(push, 1)

struct COFF_FileHdr{
	unsigned short usMagic;  // ħ������
	unsigned short usNumSec;  // �ڣ�Section����
	unsigned long  ulTime;  // ʱ���
	unsigned long  ulSymbolOffset;  // ���ű�ƫ��
	unsigned long  ulNumSymbol;  // ������
	unsigned short usOptHdrSZ;  // ��ѡͷ����
	unsigned short usFlags;  // �ļ����
};

struct COFF_SectionHdr{
	char           cName[8];  // ����
	unsigned long  ulVSize;  // �����С
	unsigned long  ulVAddr;  // �����ַ
	unsigned long  ulSize;  // �ڳ���
	unsigned long  ulSecOffset;  // ������ƫ��
	unsigned long  ulRelOffset;  // ���ض�λ��ƫ��
	unsigned long  ulLNOffset;  // �кű�ƫ��
	unsigned short ulNumRel;  // �ض�λ��Ԫ�ظ���
	unsigned short ulNumLN;  // �кű���
	unsigned long  ulFlags;  // �ڱ�ʶ
};

struct COFF_Relocation{
	unsigned long  ulAddr;  // ��λƫ��
	unsigned long  ulSymbol;  // ����
	unsigned short usType;  // ��λ����
};

struct COFF_Symbol{
	union {
		char cName[8];            // ��������
		struct {
			unsigned long ulZero;   // �ַ������ʶ
			unsigned long ulOffset; // �ַ���ƫ��
		} longName;
	}  name;
	unsigned long ulValue;     // ����ֵ
	short iSection;            // �������ڽ�
	unsigned short usType;     // ��������
	unsigned char usClass;     // ���Ŵ洢����
	unsigned char usNumAux;    // ���Ÿ��Ӽ�¼��
};

#pragma pack(pop)

struct LinkInfo
{
	COFF_FileHdr * fileHdr;
	char * strTable;
	struct COFF_Symbol * symbolTable;
	struct COFF_SectionHdr * sectionHdrs;
	char * fileContent;	
};

struct Program
{
	char * entry;
	char * wholeProgram;	
};
//������ֻ����һ��obj�ļ��ڵĴ��룬���������ⲿ����
struct Program * linkFunction(char * funcName, char * objFileName);

void freeProgram(struct Program * );

#endif