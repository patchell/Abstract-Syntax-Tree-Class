#pragma once

constexpr auto LEX_BUFF_SIZE = 256;

class CLexer
{
	FILE* m_pInFile;
	CSymTab m_SymTab;
	int m_Line;
	int m_Col;
	int m_LexBuffIndex;
	char m_aLexBuff[LEX_BUFF_SIZE];
	int m_UnGetBuff;
	CSymbol* m_pLexSymbol;
	int m_Number;
public:
	CLexer();
	virtual ~CLexer();
	BOOL Create(FILE* pInFile);
	void Error(FILE* pO, const char* pErrorString);
	CSymTab* GetSymTab() { return &m_SymTab; }
	int LexGet();
	void LexUnGet(int Value);
	BOOL IsValidNumber(int c);
	BOOL IsValidNameChar(int c);
	BOOL IsWhiteSpace(int c);
	CToken::Token Lex();
	CBin* FindSymbol(char* pName) { return GetSymTab()->FindSymbol(pName); }
	CToken::Token Expect(CToken::Token LookaHeadToken, CToken::Token Expected);
	BOOL Accept(CToken::Token Lookahead, CToken::Token Expected);
	CSymbol* GetLexSymbol() {
		return m_pLexSymbol;
	}
	int GetLexNumber() { return m_Number; }
};

