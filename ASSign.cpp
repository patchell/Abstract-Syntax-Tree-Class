#include "Global.h"

CASSign::CASSign()
{
	SetNodeType(NodeType::ASSIGN);
}

CASSign::~CASSign()
{
}

BOOL CASSign::Create()
{
	BOOL rV = TRUE;
	CAstNode::Create();
	return rV;
}

CValue* CASSign::Process(CValue* pValue)
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

void CASSign::Print(FILE* pOut, const char *pIndentString)
{
	CAstNode::Print(pOut, pIndentString);
	fprintf(pOut, "\n");
}
