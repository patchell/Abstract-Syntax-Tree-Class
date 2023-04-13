#pragma once

class CDIVop : public CAstNode
{
public:
	CDIVop();
	virtual ~CDIVop();
	BOOL Create();
	virtual CValue* Process(CValue* pValue);
	virtual void Print(FILE* pOut, const char* pIndentString);
};

