#include "Global.h"

CSymbol::CSymbol()
{
	m_Token = CToken::Token(0);
}

CSymbol::~CSymbol()
{
}

BOOL CSymbol::Create(char* pName)
{
	BOOL rV = TRUE;

	SetName(pName);
	return rV;
}

BOOL CSymbol::Compare(const char* name)
{
	BOOL rV = FALSE;

	if (strcmp(GetName(), name) == 0)
		rV = TRUE;
	return rV;
}

void CSymbol::Print(FILE* pOut, BOOL bEOL)
{
	fprintf(pOut, ":%s", GetName());
	if (bEOL)
		fprintf(pOut, "\n");
}
