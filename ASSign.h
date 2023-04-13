#pragma once

class CASSign : public CAstNode
{
public:
	CASSign();
	virtual ~CASSign();
	BOOL Create();
	virtual CValue* Process(CValue* pValue);
	virtual void Print(FILE* pOut, const char* pIndentString);
};

