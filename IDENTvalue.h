#pragma once

class CIDENTvalue : public CAstNode
{
	CSymbol* m_pSym;
public:
	CIDENTvalue();
	virtual ~CIDENTvalue();
	BOOL Create();
	virtual CValue* Process(CValue* pValue);
	void SetSymbol(CSymbol* pSym) { m_pSym = pSym; }
	CSymbol* GetSymbol() { return m_pSym; }
	virtual void Print(FILE* pOut, const char* pIndentString);
};

