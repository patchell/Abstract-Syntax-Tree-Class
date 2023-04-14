#include "Global.h"

CParser::CParser()
{
	m_LookaHead = CToken::Token(0);
	m_pOutFile = 0;
}

CParser::~CParser()
{
}

BOOL CParser::Create(FILE* pIn, FILE* pOut)
{
	BOOL rV = TRUE;

	m_pOutFile = pOut;
	m_Lexer.Create(pIn);
	return rV;
}

void CParser::Parse()
{
	CAstNode* pN;

	m_LookaHead = Lex();
	pN = Grammar();
	m_RootNode.Create();
	m_RootNode.AddNode(pN, NULL);
	fprintf(GetOutFile(), "----------------------------------\n");
	m_RootNode.PrintTree(GetOutFile());
}

CAstNode* CParser::Grammar()
{
	//----------------------------------------------
	// Assign	-> IDENT = Expr ';' Assign
	//			-> .
	// 
	// Don't know, works ok, but it is really 
	// ugly.
	//----------------------------------------------
	CASSign* pAssNode = 0;
	CASSign* pFirstAss = 0;
	CAstNode* pN = 0, * pN1 = 0;
	CIDENTvalue* pIdentAstNode;
	BOOL Loop = TRUE;

	//--------------------------------------
	// Keep looping until we run out of
	// Tokens
	// 
	// Implemented as a while loop rather
	// than recursive.  Makes life so much
	// easier.
	//--------------------------------------
	while (Loop)
	{
		switch (m_LookaHead)
		{
		case CToken::Token::IDENT:
			if (pN)
			{
				//----------------------------------
				// There after
				// 
				//  create an assignment node and
				// add it to the list of statements
				//----------------------------------
				pAssNode = new CASSign;
				pAssNode->Create();
				pN->AddNextNode(pAssNode);
			}
			else
			{
				//------------------------
				// The first time though
				// 
				// Create an assignment
				// node
				//------------------------
				pAssNode = new CASSign;
				pAssNode->Create();
				pFirstAss = pAssNode;
			}
			//--------------------------------------------
			// Create the identifier node
			//--------------------------------------------
			pIdentAstNode = new CIDENTvalue;
			pIdentAstNode->Create();
			pIdentAstNode->SetSymbol(GetLexer()->GetLexSymbol());
			//-------------------------------------
			m_LookaHead = Expect(CToken::Token::IDENT);
			m_LookaHead = Expect(CToken::Token('='));
			//-------------------------------------
			// parse the expresion and get the
			// head node for that.
			//-------------------------------------
			pN1 = Expr();
			//-------------------------------------
			// Then add the identifier node to
			// the assignmet node as  a child
			// with the expresion node as next
			//-------------------------------------
			pAssNode->AddNode(pIdentAstNode, pN1);
			pN = pAssNode;	//get ready to do it again.
			m_LookaHead = Expect(CToken::Token(';'));
			break;
		default:
			//--------------------------
			// unrecognized token, time
			// to quit
			//--------------------------
			Loop = FALSE;
			break;
		}
	}
	return pFirstAss;
}


CAstNode* CParser::Expr()
{
	//----------------------------------------------
	// Expr		-> Term Expr_1;
	// Expr_1	-> + Term Expr1
	//			-> - Term Expr1
	//			-> .;
	// 
	// 
	// returns a last child node
	//----------------------------------------------
	CADDop* pAdd = 0;
	CSUBop* pSub = 0;
	CAstNode* pN1 = 0, * pN2 = 0;
	BOOL Loop = TRUE;

	pN1 = Term();	//child
	while (Loop)
	{
		switch (m_LookaHead)
		{
		case CToken::Token('+'):
			m_LookaHead = Expect(CToken::Token('+'));
			pN2 = Term();	//next
			pAdd = new CADDop;
			pAdd->Create();
			pAdd->AddNode(pN1, pN2);
			pN1 = pAdd;
			break;
		case CToken::Token('-'):
			m_LookaHead = Expect(CToken::Token('-'));
			pN2 = Term();
			pSub = new CSUBop;
			pSub->Create();
			pSub->AddNode(pN1, pN2);
			pN1 = pSub;
			break;
		default:
			Loop = FALSE;
			break;
		}
	}
	return pN1;
}

CAstNode* CParser::Term()
{
	//----------------------------------------------
	// Term		-> Factor Term_1;'
	// Term_1	-> * Factor Term_1
	//			-> / Factor Term_1
	//			-> .;
	//----------------------------------------------
	CAstNode* pN1 = 0, * pN2 = 0;
	BOOL Loop = TRUE;
	CMULop* pMul = 0;
	CDIVop* pDiv = 0;

	pN1 = Factor();
	while (Loop)
	{
		switch (m_LookaHead)
		{
		case CToken::Token('*'):
			m_LookaHead = Expect(CToken::Token('*'));
			pN2 = Factor();
			pMul = new CMULop;
			pMul->Create();
			pMul->AddNode(pN1, pN2);
			pN1 = pMul;
			break;
		case CToken::Token('/'):
			m_LookaHead = Expect(CToken::Token('/'));
			pN2 = Factor();
			pDiv = new CDIVop;
			pDiv->Create();
			pDiv->AddNode(pN1, pN2);
			pN1 = pDiv;
			break;
		default:
			Loop = 0;
			break;
		}
	}
	return pN1;
}

CAstNode* CParser::Factor()
{
	//----------------------------------------------
	// Factor	-> IDENT
	//			-> NUMBER
	//			-> ( Expr );
	//----------------------------------------------
	CAstNode* pN = 0;
	CNUMvalue* pNUM = 0;
	CIDENTvalue* pIDENT = 0;

	switch (m_LookaHead)
	{
	case CToken::Token::IDENT:
		pIDENT = new CIDENTvalue;
		pIDENT->Create();
		pIDENT->SetSymbol(GetLexer()->GetLexSymbol());
		m_LookaHead = Expect(CToken::Token::IDENT);
		pN = pIDENT;
		break;
	case CToken::Token::NUMBER:
		pNUM = new CNUMvalue;
		pNUM->Create();
		pNUM->SetValue(GetLexer()->GetLexNumber());
		pNUM->Print(GetOutFile(), "");
		m_LookaHead = Expect(CToken::Token::NUMBER);
		pN = pNUM;
		break;
	case CToken::Token('('):
		m_LookaHead = Expect(CToken::Token('('));
		pN = Expr();
		m_LookaHead = Expect(CToken::Token(')'));
		break;
	}
	return pN;
}
