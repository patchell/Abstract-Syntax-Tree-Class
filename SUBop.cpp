#include "Global.h"

CSUBop::CSUBop()
{
	SetNodeType(NodeType::SUBOP);
}

CSUBop::~CSUBop()
{
}

BOOL CSUBop::Create()
{
	BOOL rV = TRUE;
	CAstNode::Create();
	return rV;
}

CValue* CSUBop::Process(CValue* pValue)
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

void CSUBop::Print(FILE* pOut, const char* pIndentString)
{
	CAstNode::Print(pOut, pIndentString);
	fprintf(pOut, "\n");
}
