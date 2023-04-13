#pragma once

class CNUMvalue : public CAstNode
{
	CValue* m_pValue;
public:
	CNUMvalue();
	virtual ~CNUMvalue();
	BOOL Create();
	virtual CValue* Process(CValue* pValue);
	void SetValue(int v) { m_pValue->SetValue(v); }
	int GetValue() { return m_pValue->GetValue(); }
	virtual void Print(FILE * pOut, const char* pIndentString);
};