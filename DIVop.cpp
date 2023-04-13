#include "Global.h"

CDIVop::CDIVop()
{
	SetNodeType(NodeType::DIVOP);
}

CDIVop::~CDIVop()
{
}

BOOL CDIVop::Create()
{
	BOOL rV = TRUE;
	CAstNode::Create();
	return rV;
}

CValue* CDIVop::Process(CValue* pValue)
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

void CDIVop::Print(FILE* pOut, const char* pIndentString)
{
	CAstNode::Print(pOut, pIndentString);
	fprintf(pOut, "\n");
}
