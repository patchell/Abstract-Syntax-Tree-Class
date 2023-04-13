#pragma once

class CROOTnode : public CAstNode
{
public:
	CROOTnode();
	virtual ~CROOTnode();
	BOOL Create();
	virtual CValue* Process(CValue* pValue);
	virtual void Print(FILE* pOut, const char* pIndentString);
	virtual void PrintTree(FILE* pOut);
};

