#pragma once

class CSUBop : public CAstNode
{
public:
	CSUBop();
	virtual ~CSUBop();
	BOOL Create();
	virtual CValue* Process(CValue* pValue);
	virtual void Print(FILE* pOut, const char* pIndentString);
};

