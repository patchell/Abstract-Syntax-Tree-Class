#pragma once

class CADDop : public CAstNode
{
public:
	CADDop();
	virtual ~CADDop();
	BOOL Create();
	virtual CValue* Process(CValue* pValue);
	virtual void Print(FILE* pOut, const char* pIndentString);
};

