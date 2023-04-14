#include "Global.h"

CAstNode::CAstNode()
{
	m_nNumberOfNodes = 0;
	m_pNext = 0;
	m_pChild = 0;
	m_pTail = 0;
	m_NodeType = NodeType::BASE;
	m_NodeNumber = ++s_NodeNumber;
}

CAstNode::~CAstNode()
{
}

BOOL CAstNode::Create()
{
	BOOL rV = TRUE;
	return rV;
}

CValue* CAstNode::Process(CValue* pValue)
{
	//------------------------------------
	// This is where all the work is done.
	// It will probaly take this form in
	// the method in the derived class:
	// 
	// CValue* pVal1,*pVal2;
	// CAstNode* pAN;
	// 
	// if(GetChild())
	//	pVal1 = GetChild()->Process(pValIn);
	// pAN = GetNext();
	// while(pAN)
	// {
	//	pVal2 = pAN->Process(pVal1);
	//		.....
	//		Do Something
	//		....
	//	pVal1 = pVal2;
	//	pAN = pAN->GetNext();
	// }
	// return pVal1;
	// 
	// But, there may be ocasions where it
	// might need to be different
	//------------------------------------
	return nullptr;
}

void CAstNode::AddNode(CAstNode* pChild, CAstNode* pNext)
{
	SetChild(pChild);
	if (GetChild())
	{
		GetChild()->AddNextNode(pNext);
	}
}

void CAstNode::AddNextNode(CAstNode* pNext)
{
	//------------------------------------
	// AddNextNode
	// Adds a new node at the end of the
	// next list for this node
	//------------------------------------
	if (pNext)
	{
		if (GetTail())
		{
			GetTail()->SetNext(pNext);
			SetTail(pNext);
		}
		else
		{
			SetTail(pNext);
			SetNext(pNext);
		}
		++m_nNumberOfNodes;
	}
}

const char* CAstNode::GetTypeName()
{
	const char* pName = 0;
	int i;

	for (i = 0; i < NUMBER_OF_NODE_TYPES; ++i)
	{
		if (GetNodeType() == m_NodeNames[i].m_Type)
		{
			pName = m_NodeNames[i].m_pName;
			i = NUMBER_OF_NODE_TYPES;
		}
	}
	return pName;
}

void CAstNode::Print(FILE* pOut, const char *pIndentString)
{
	char* s = new char[512];
	int Next, Child, Tail;
	int l;

	l = sprintf_s(s, 512, "%s", pIndentString);
	if (!pIndentString)
		pIndentString = "";
	if (GetNext())
		Next = GetNext()->GetNodeNumber();
	else
		Next = -1;
	if (GetChild())
		Child = GetChild()->GetNodeNumber();
	else
		Child = -1;
	if (GetTail())
		Tail = GetTail()->GetNodeNumber();
	else
		Tail = -1;
		
	fprintf(pOut, "%5d%5d%5d%5d   %s+-%s-",
		GetNodeNumber(),
		Next,
		Child,
		Tail,
		pIndentString,
		GetTypeName()
	);
	delete[]s;
}

void CAstNode::PrintBranch(FILE* pOut, char *pIndentString)
{
	char* s = new char[512];	// copy of indent string
	int l = 0;
	CAstNode* pAN;

	l = sprintf_s(s, 512, "%s", pIndentString);
	Print(pOut, s);
	if (GetChild())
	{
		if (GetNext())
			l += sprintf_s(&s[l], 512 - l, "%s", "|  ");
		else
			l += sprintf_s(&s[l], 512 - l, "%s", "   ");
		GetChild()->PrintBranch(pOut, s);
		l -= 3;
		s[l] = 0;
	}
	pAN = GetNext();
	while (pAN)
	{
		pAN->PrintBranch(pOut, s);
		pAN = pAN->GetNext();
	}
	delete[] s;
}
