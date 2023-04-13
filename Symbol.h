#pragma once

class CSymbol: CBin
{
	CToken::Token m_Token;
public:
	CSymbol();
	virtual ~CSymbol();
	BOOL Create(char *pName);
	virtual BOOL Compare(const char* name);
	CToken::Token GetTokenValue() { return m_Token; }
	void SetTokenValue(CToken::Token TokenvValue) {
		m_Token = TokenvValue;
	}
	virtual void Print(FILE* pOut, BOOL bEOL);
};

