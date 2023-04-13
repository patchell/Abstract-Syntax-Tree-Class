#include "Global.h"

CNUMvalue::CNUMvalue()
{
	m_pValue = 0;
	SetNodeType(NodeType::NUMBER);
}

CNUMvalue::~CNUMvalue()
{
}

BOOL CNUMvalue::Create()
{
	BOOL rV = TRUE;

	m_pValue = new CValue;
	rV = m_pValue->Create();
	return 0;
}

CValue* CNUMvalue::Process(CValue* pValue)
{
	return nullptr;
}

void CNUMvalue::Print(FILE* pOut, const char* pIndentString)
{
	CAstNode::Print(pOut, pIndentString);
	fprintf(pOut, ":%d", GetValue());
	fprintf(pOut, "\n");
}
