#pragma once

class CParser
{
	FILE* m_pOutFile;
	CToken::Token m_LookaHead;
	CROOTnode m_RootNode;
	CLexer m_Lexer;
public:
	CParser();
	virtual ~CParser();
	BOOL Create(FILE* pIn, FILE* pOut);
	void Parse();
	//--------------------------------------
	// Lexer/Symbol Table
	//--------------------------------------
	CLexer* GetLexer() { return &m_Lexer; }
	CToken::Token Lex() { return GetLexer()->Lex(); }
	CToken::Token Expect(CToken::Token ExpectedToken) {
		return GetLexer()->Expect(m_LookaHead, ExpectedToken);
	}
	CSymTab* GetSymTab() { return GetLexer()->GetSymTab(); }
	void AddSymbol(CBin* pSym) { GetSymTab()->AddSymbol(pSym); }
	FILE* GetOutFile() { return m_pOutFile; }
	CROOTnode* GetRootNode() { return &m_RootNode; }
private:
	CAstNode* Grammar();
	CAstNode* Expr();
	CAstNode* Term();
	CAstNode* Factor();
};

