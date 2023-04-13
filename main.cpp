#include "Global.h"

FILE* pInFile = 0;
FILE* pOutFile = 0;

FILE* GetOutFile()
{
	return pOutFile;
}
char* TreeIndent(
	char* s, 
	int MainChar, 
	int LastChar,
	int Indent
)
{
	int i = 0;
	int l;

	if (Indent == 0)
	{
		s[0] = LastChar;
		s[1] = 0;
	}
	else
	{
		l = 0;
		do 
		{
			if (Indent)
				l += sprintf_s(&s[l], 256 - l, "%c  ", MainChar);
			else
				l += sprintf_s(&s[l], 256 - l, "%c", LastChar);
		} while (Indent--);
	}
	return s;
}

void CloseAllFiles()
{
	fclose(pInFile);
	fclose(pOutFile);
}

int main(int argc, char* argv[])
{
	int ExitCode = 0;
	char OutName[256];
	char* pC;
	CParser Parser;

	fopen_s(&pInFile, argv[1],"r");
	if (!pInFile)
	{
		fprintf(stderr, "could not open %s\n", argv[1]);
		exit(1);
	}
	strcpy_s(OutName, 256, argv[1]);
	pC = strrchr(OutName, '.');
	++pC;
	sprintf_s(pC, 16, ".out.txt");
	fopen_s(&pOutFile, OutName, "w");
	Parser.Create(pInFile, pOutFile);
	fprintf(stderr, "AST Version 0.0.2\n");
	fprintf(stderr, "Input File :%s\n", argv[1]);
	Parser.Parse();
	fprintf(stderr, "Output File:%s\n", OutName);
	CloseAllFiles();
	fprintf(stderr, "Done\n");
	return ExitCode;
}