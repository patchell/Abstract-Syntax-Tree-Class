#pragma once

class CValue
{
	int m_Value;
public:
	CValue();
	virtual ~CValue();
	BOOL Create();
	void SetValue(int v) { m_Value = v; }
	int GetValue() { return m_Value; }
};

