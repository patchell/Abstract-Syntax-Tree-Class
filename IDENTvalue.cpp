#include "Global.h"


CIDENTvalue::CIDENTvalue()
{
	m_pSym = 0;
	SetNodeType(NodeType::IDENT);
}

CIDENTvalue::~CIDENTvalue()
{
}

BOOL CIDENTvalue::Create()
{
	BOOL rV = TRUE;

	rV = CAstNode::Create();
	return rV;
}

CValue* CIDENTvalue::Process(CValue* pValue)
{
	return nullptr;
}

void CIDENTvalue::Print(FILE* pOut, const char* pIndentString)
{
	CAstNode::Print(pOut, pIndentString);
	GetSymbol()->Print(pOut, TRUE);
}
