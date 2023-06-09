#pragma once

constexpr auto SYMTAB_SIZE = 101;

class CSymTab
{
	int Hash(const char* name);
protected:
	int m_nElements;	//total number of elements in table
	int m_tSize;	//depth of table
	CBucket** m_ppTab;	//pointer to table
public:
	CSymTab() {
		m_ppTab = 0;
		m_nElements = 0;
		m_tSize = 0;
	}
	virtual ~CSymTab();
	BOOL Create(int TableDepth);
	virtual CBin* FindSymbol(const char* name);
	virtual void AddSymbol(CBin* pSym);
	virtual void DelSymbol(CBin* pSym);
	int GetNumElements() { return m_nElements; }
	int GetTableSize() { return m_tSize; }
	CBucket** GetTable() { return m_ppTab; }
	CBucket* GetBucket(int i) { return m_ppTab[i]; }
	//-----------------------------------
	// Debug
	//-----------------------------------
	virtual void PrintTable(FILE* pOut);
};

