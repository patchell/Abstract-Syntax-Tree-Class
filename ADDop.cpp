#include "Global.h"

CADDop::CADDop()
{
	SetNodeType(NodeType::ADDOP);
}

CADDop::~CADDop()
{
}

BOOL CADDop::Create()
{
	BOOL rV = TRUE;
	CAstNode::Create();
	return rV;
}

CValue* CADDop::Process(CValue* pValue)
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

void CADDop::Print(FILE* pOut, const char* pIndentString)
{
	CAstNode::Print(pOut, pIndentString);
	fprintf(pOut, "\n");
}
