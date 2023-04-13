#pragma once

//--------------------------------------
// Abstract Syntax Tree node (AST)
// Base Class for an AST node
//--------------------------------------
constexpr auto NUMBER_OF_NODE_TYPES = 9;

class CAstNode
{
public:
	enum class NodeType {
		BASE,
		ROOT,
		IDENT,
		NUMBER,
		ASSIGN,
		ADDOP,
		SUBOP,
		MULOP,
		DIVOP,

	};
	struct NoneNamesLU {
		NodeType m_Type;
		const char* m_pName;
	};
	inline static NoneNamesLU m_NodeNames[NUMBER_OF_NODE_TYPES] = {
		{NodeType::BASE, "BASE"},
		{NodeType::ROOT, "ROOT"},
		{NodeType::IDENT, "IDENT"},
		{NodeType::NUMBER, "NUMBER"},
		{NodeType::ASSIGN, "ASSIGN"},
		{NodeType::ADDOP, "ADDOP"},
		{NodeType::SUBOP, "SUBOP"},
		{NodeType::MULOP, "MULOP"},
		{NodeType::DIVOP, "DIVOP"}
	};
private:
	inline static int s_NodeNumber = 0;
	CAstNode* m_pHead;
	CAstNode* m_pTail;
	CAstNode* m_pNext;
	CAstNode* m_pPrev;
	CAstNode* m_pChild;
	int m_NodeNumber;
	int m_nNumberOfNodes;
	NodeType m_NodeType;
public:
	CAstNode();
	virtual ~CAstNode();
	BOOL Create();
	virtual CValue* Process(CValue* pValue) { return 0; };
	//--------------------------------
	// Linked List
	//--------------------------------
	void SetNext(CAstNode* pN) { m_pNext = pN; }
	CAstNode* GetNext() { return m_pNext; }
	void SetPrev(CAstNode* pP) { m_pPrev = pP; }
	CAstNode* GetPrev() { return m_pPrev; }
	CAstNode* GetChild() { return m_pChild; }
	void SetChild(CAstNode* pC){m_pChild = pC; }
	void AddNode(CAstNode* pChild, CAstNode* pNext);
	void AddNextNode(CAstNode* pNext);
	void SetHead(CAstNode* pH) { m_pHead = pH; }
	CAstNode* GetHead() { return m_pHead; }
	void SetTail(CAstNode* pT) { m_pTail = pT; }
	CAstNode* GetTail() { return m_pTail; }
	//--------------------------------
	// Node ID
	//--------------------------------
	int GetNodeNumber() { 
		return m_NodeNumber; 
	}
	NodeType GetNodeType() { return m_NodeType; }
    void PrintBranch(FILE* pOut, char* pIndentString);
	virtual void Print(FILE* pOut, const char* pIndentString);
	const char* GetTypeName();
protected:
	void SetNodeType(NodeType NT) { m_NodeType = NT; }
};

