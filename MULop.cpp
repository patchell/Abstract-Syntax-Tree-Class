#include "Global.h"

CMULop::CMULop()
{
	SetNodeType(NodeType::MULOP);
}

CMULop::~CMULop()
{
}

BOOL CMULop::Create()
{
	BOOL rV = TRUE;
	CAstNode::Create();
	return rV;
}

CValue* CMULop::Process(CValue* pValue)
{
	if (GetChild())
	{
		pValue = GetChild()->Process(pValue);
	}
	if (GetNext())
	{
		pValue = GetNext()->Process(pValue);
	}
	return pValue;
}

void CMULop::Print(FILE* pOut, const char* pIndentString)
{
	CAstNode::Print(pOut, pIndentString);
	fprintf(pOut, "\n");
}
