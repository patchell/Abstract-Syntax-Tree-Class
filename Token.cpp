#include "Global.h"

CToken::CToken()
{
}

CToken::~CToken()
{
}

BOOL CToken::Create()
{
	BOOL rV = TRUE;
	return rV;
}

const char* CToken::LookupName(Token aToken)
{
	const char* pTokenName = 0;
	int i;
	BOOL Loop = TRUE;

	for (i = 0; (i < TOTAL_TOKENS) && Loop; ++i)
	{
		if (TNames[i].TokenVal == aToken)
		{
			pTokenName = TNames[i].pName;
			Loop = FALSE;
		}
	}
	return pTokenName;
}
