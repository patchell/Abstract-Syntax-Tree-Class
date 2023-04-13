#include "Global.h"

CLexer::CLexer()
{
	int i;

	m_UnGetBuff = 0;
	m_LexBuffIndex = 0;
	m_pInFile = 0;
	m_Line = 1;
	m_Col = 1;
	m_pLexSymbol = 0;
	m_Number = 0;
	for (i = 0; i < LEX_BUFF_SIZE; ++i)
	{
		m_aLexBuff[i] = 0;
	}
}

CLexer::~CLexer()
{
}

BOOL CLexer::Create(FILE* pInFile)
{
	BOOL rV = TRUE;

	m_pInFile = pInFile;
	m_SymTab.Create(11);
	return rV;
}

void CLexer::Error(FILE* pO, const char* pErrorString)
{
	fprintf(pO, "Line %d  Col %d Error:%s\n", m_Line, m_Col, pErrorString);
	CloseAllFiles();
}

int CLexer::LexGet()
{
	int c = 0;

	if (m_UnGetBuff)
	{
		c = m_UnGetBuff;
		m_UnGetBuff = 0;
	}
	else
	{
		if (m_pInFile)
			c = fgetc(m_pInFile);
		else
			c = EOF;
	}
	if (c == '\n')
	{
		m_Col = 1;
		m_Line++;
	}
	else
	{
		m_Col++;
	}
	return c;
}

void CLexer::LexUnGet(int Value)
{
	m_UnGetBuff = Value;
}

BOOL CLexer::IsValidNumber(int c)
{
	BOOL IsValid = FALSE;

	switch (c)
	{
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
		IsValid = TRUE;
		break;
	}
	return IsValid;
}

BOOL CLexer::IsValidNameChar(int c)
{
	BOOL IsValid = FALSE;

	if (isalnum(c) || c == '_')
		IsValid = TRUE;
	return IsValid;
}

BOOL CLexer::IsWhiteSpace(int c)
{
	BOOL IsValid = FALSE;

	switch (c)
	{
	case '\n':
		m_Line++;
		m_Col = 0;
	case '\r':
	case '\t':
	case ' ':
		IsValid = TRUE;
		break;
	}
	return IsValid;
}

CToken::Token CLexer::Lex()
{
	BOOL Loop = TRUE;
	BOOL auxLoop = TRUE;
	int c;
	CToken::Token TokenValue = CToken::Token(0);

	m_LexBuffIndex = 0;
	m_aLexBuff[1] = 0;
	m_pLexSymbol = 0;
	while (Loop)
	{
		c = LexGet();
		m_aLexBuff[0] = c;

		switch (c)
		{
		case EOF:
			TokenValue = CToken::Token(EOF);
			Loop = FALSE;
			break;
		case '\n':	//white space
		case '\r':
		case ' ':
			break;
		case '\t':	//more white space
			m_Col += 4;
			break;
		case '0':case '1':case '2':case '3':case '4':
		case '5':case '6':case '7':case '8':case '9':
		case '-':
			if (c == '-')
			{
				int c1;
				c1 = LexGet();
				if (!IsValidNumber(c1))
				{
					LexUnGet(c1);
					TokenValue = CToken::Token(c);
					Loop = FALSE;
				}
				else
				{
					m_aLexBuff[m_LexBuffIndex++] = c;
					m_aLexBuff[m_LexBuffIndex++] = c1;
					c = LexGet();
				}
			}
			if (Loop)
			{
				while (IsValidNumber(c))
				{
					m_aLexBuff[m_LexBuffIndex++] = c;
					c = LexGet();
				}
				m_aLexBuff[m_LexBuffIndex] = 0;
				m_Number = atoi(m_aLexBuff);
				Loop = FALSE;
				TokenValue = CToken::Token::NUMBER;
				LexUnGet(c);
			}
			break;
		case '=':	//misc tokens
		case ';':
		case '+':
		case '*':
		case '/':
		case '(':
		case ')':
			TokenValue = CToken::Token(c);
			Loop = FALSE;
			break;
		default:	//Identifiers
			m_aLexBuff[m_LexBuffIndex++] = c;
			auxLoop = TRUE;
			while (auxLoop)
			{
				c = LexGet();
				if (IsValidNameChar(c))
				{
					m_aLexBuff[m_LexBuffIndex++] = c;
				}
				else
				{
					auxLoop = FALSE;
					m_aLexBuff[m_LexBuffIndex] = 0;
					LexUnGet(c);
				}
			}	//END OF collecting characters for word
			//-------------------------------------
			// Is it Already Defined Identifier?
			//-------------------------------------
			m_pLexSymbol = (CSymbol*)FindSymbol(m_aLexBuff);
			if (m_pLexSymbol)
			{
				TokenValue = m_pLexSymbol->GetTokenValue();
				Loop = FALSE;
			}
			else
			{
				//-------------------------------------
				// Identifier is New/Undefined
				//-------------------------------------
				m_pLexSymbol = new CSymbol;
				m_pLexSymbol->Create(m_aLexBuff);
				TokenValue = CToken::Token::IDENT;
				m_pLexSymbol->SetTokenValue(CToken::Token::IDENT);
				Loop = FALSE;
			}
			break;	// end of default:
		}	// End of switch(c)
	}
	//	fprintf(LogFile(), "Lex::%s\n", m_aLexBuff);
	return TokenValue;
}


//**********************************************
// Expect
//
// This function is used to check that we get
// the token that we Expect.
//
// parameters:
//	Lookahead..Current lookahead token
//	token....this is the token we Expect
// return value:
//	reutns the next Lookahead token (>0)
//	reutnrs 0 or negative if we did not get what we Expected
//*********************************************

CToken::Token CLexer::Expect(CToken::Token LookaHeadToken, CToken::Token Expected)
{
	if (Accept(LookaHeadToken, Expected))
		LookaHeadToken = Lex();
	else
	{
		fprintf(stderr, "Line %d: Unexpected Token:Got %d Expected %d\n", m_Line, LookaHeadToken, Expected);
		exit(1);
	}
	return LookaHeadToken;
}

//********************************************
// Accept
//
// This function compares the token you want
// versus the token that is current.  If they
// match, then we get another token.
// If not, then just return.
//
// parameter:
//	Lookahead..The current lookahead token
//	token.....this is the token we want
//
// return value:
//	returns the new token value (>0)
//	returns 0 or negative if we don't get the token we want
//**********************************************

BOOL CLexer::Accept(CToken::Token Lookahead, CToken::Token Expected)
{
	BOOL rv = FALSE;

	if (Expected == Lookahead)
		rv = TRUE;
	return rv;
}
