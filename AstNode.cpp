#include "Global.h"

CAstNode::CAstNode()
{
	m_nNumberOfNodes = 0;
	m_pNext = 0;
	m_pPrev = 0;
	m_pChild = 0;
	m_pHead = 0;
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

void CAstNode::AddNode(CAstNode* pChild, CAstNode* pNext)
{
	SetChild(pChild);
	if (pChild)
		pChild->AddNextNode(pNext);
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
			pNext->SetPrev(GetTail());
			SetTail(pNext);
		}
		else
		{
			SetTail(pNext);
			SetHead(pNext);
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
	int Next, Child, Tail, Head;

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
	if (!m_pTail)
		Tail = -1;
	else
	{
		Tail = GetTail()->GetNodeNumber();
	}
	if (!m_pHead)
		Head = -1;
	else
		Head = GetHead()->GetNodeNumber();
		
	fprintf(pOut, "%5d%5d%5d%5d%5d   %s",
		GetNodeNumber(),
		Head,
		Next,
		Child,
		Tail,
		pIndentString
	);
	//-------------------------------------
	// Print out node type Name
	//-------------------------------------
	fprintf(pOut, "-%s-", GetTypeName());
}

void CAstNode::PrintBranch(FILE* pOut, char *pIndentString)
{
	char* s = new char[256];
	int l = 0;

	l = sprintf_s(s, 256, "%s", pIndentString);

	do {
		l += sprintf_s(&s[l], 256 - l, "+ -");
		Print(pOut, s);
		l -= 3;
		s[l] = 0;
		if (GetChild())
		{
			if(GetHead())
				l += sprintf_s(&s[l], 256 - l, "|  ");
			else if (GetNext())
				l += sprintf_s(&s[l], 256 - l, "|  ");
			else
				l += sprintf_s(&s[l], 256 - l, "   ");
			GetChild()->PrintBranch(pOut, s);
			l -= 3;
			s[l] = 0;
		}
		if (GetHead())
			GetHead()->PrintBranch(pOut, s);
	} while (GetNext());
}

/*
void CAstNode::PrintBranch(FILE* pOut, int Indent)
{
	CAstNode* pASTN = 0;

	static int Recursions = 0;
	fprintf(stderr, "Recursion %d\n", ++Recursions);
	if (Recursions > 30)
	{
		fprintf(stderr, "Infinate Loop %d\n", Recursions);
		exit(1);
	}

	Print(pOut, Indent);
	if (GetChild())
	{
		GetChild()->PrintBranch(pOut, Indent + 1);
	}
	if (GetHead())
	{
		pASTN = GetHead();
		while (pASTN)
		{
			pASTN->PrintBranch(pOut, Indent);
			pASTN = pASTN->GetNext();
		}
	}
}

*/