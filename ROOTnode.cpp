#include "Global.h"

CROOTnode::CROOTnode()
{
	SetNodeType(NodeType::ROOT);
}

CROOTnode::~CROOTnode()
{
}

BOOL CROOTnode::Create()
{
	return 0;
}

CValue* CROOTnode::Process(CValue* pValue)
{
	return nullptr;
}

void CROOTnode::Print(FILE* pOut, const char* pIndentString)
{
	CAstNode::Print(pOut, pIndentString);
	fprintf(pOut, "\n");
}

void CROOTnode::PrintTree(FILE* pOut)
{
	char* s = new char[256];

	s[0] = 0;
	fprintf(pOut, "  NODE NEXT CHILD TAIL\n");
	PrintBranch(pOut, s);
	delete[] s;
}
