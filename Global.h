#ifndef GLOBAL__H
#define GLOBAL__H

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Token.h"
#include "Value.h"
#include "AstNode.h"
#include "Bin.h"
#include "Bucket.h"
#include "Symbol.h"
//---------------------
// AST Node Objects
//---------------------
#include "ADDop.h"
#include "ASSign.h"
#include "DIVop.h"
#include "IDENTvalue.h"
#include "MULop.h"
#include "NUMvalue.h"
#include "ROOTnode.h"
#include "SUBop.h"

#include "SymTab.h"
#include "Lexer.h"
#include "Parser.h"

extern void CloseAllFiles();
extern char* TreeIndent(
	char* s,
	int MainChar,
	int LastChar,
	int Indent
);
extern FILE* GetOutFile();

#endif

