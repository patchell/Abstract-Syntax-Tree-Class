#pragma once

class CMULop : public CAstNode
{
public:
	CMULop();
	virtual ~CMULop();
	BOOL Create();
	virtual CValue* Process(CValue* pValue);
	virtual void Print(FILE* pOut, const char* pIndentString);
};

