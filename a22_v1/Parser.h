/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2023
* Author: Philogene Villanueva, Tasfia Khan Aohana
* Professors: Paulo Sousa
************************************************************
=--------------------------------------------------------=
||          COMPILERS - ALGONQUIN COLLEGE (F23)         ||
|=------------------------------------------------------=|
||                                                      ||
||                   		_-_.                        ||
||	         			 _-',^. `-_.                    ||
||	        		 ._-' ,'   `.   `-_                 ||
||	        		!`-_._________`-':::                ||
||	        		!   /\        /\::::                ||
||	        		;  /  \      /..\:::                ||
||	        		! /    \    /....\::                ||
||	        		!/      \  /......\:                ||
||		        	;--.___. \/_.__.--;;                ||
||	        		 '-_    `:!;;;;;;;'                 ||
||			        	`-_, :!;;;''                    ||
||	        			   `-!'                         ||
||                                                      ||
||     _____    __    __     _____     _____  __ __     ||
||    /\___/\  /_/\  /\_\  /\  __/\  /\_____\/_/\__/\   ||
||   / / _ \ \ ) ) \/ ( (  ) )(_ ) )( (_____/) ) ) ) )  ||
||   \ \(_)/ //_/ \  / \_\/ / __/ /  \ \__\ /_/ /_/_/   ||
||  / / _ \ \\ \ \\// / /\ \  _\ \  / /__/_\ \ \ \ \    ||
||  ( (_( )_) ))_) )( (_(  ) )(__) )( (_____\)_) ) \ \  ||
||   \/_/ \_\/ \_\/  \/_/  \/____\/  \/_____/\_\/ \_\/  ||
||                                                      ||
| =----------------------------------------------------= |
=-------------------------------------------------------=
*/

/*
************************************************************
* File name: Parser.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A32.
* Date: May 01 2023
* Professor: Paulo Sousa
* Purpose: This file is the main header for Parser (.h)
************************************************************
*/

#ifndef PARSER_H_
#define PARSER_H_

/* Inclusion section */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif
#ifndef READER_H_
#include "Reader.h"
#endif
#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/* Global vars */
static Token			lookahead;
extern BufferPointer	stringLiteralTable;
extern int32			line;
extern Token			tokenizer(amber_void);
extern string			keywordTable[KWT_SIZE];
static int32			syntaxErrorNumber = 0;

#define LANG_PCKG		"package"
#define LANG_IMPT		"import"
#define LANG_WRTE		"fmt.Println"
#define LANG_READ		"fmt.Scanln"
#define LANG_MAIN		"main()"

/* TO_DO: Create ALL constants for keywords (sequence given in table.h) */

/* Constants */
enum KEYWORDS {
	NO_ATTR = -1,
	KW_var,		/* KW00 */
	KW_int32,	/* KW01 */
	KW_float32,	/* KW02 */
	KW_string,	/* KW03 */
	KW_if,		/* KW04 */
	KW_then,	/* KW05 */
	KW_else,	/* KW06 */
	KW_package,	/* KW07 */
	KW_import,	/* KW08 */
	KW_main,	/* KW09 */
	KW_for,		/* KW10 */
	KW_func,	/* KW11 */
	KW_println,	/* KW12 */
	KW_scanln	/* KW13 */
};

/* TO_DO: Define the number of BNF rules */
#define NUM_BNF_RULES 17

/* Parser */
typedef struct parserData {
	int32 parsHistogram[NUM_BNF_RULES];	/* Number of BNF Statements */
} ParserData, * pParsData;

/* Number of errors */
int32 numParserErrors;

/* Scanner data */
ParserData psData;

/* Function definitions */
amber_void startParser();
amber_void matchToken(int32, int32);
amber_void syncErrorHandler(int32);
amber_void printError();
amber_void printBNFData(ParserData psData);

/* List of BNF statements */
enum BNF_RULES {
	BNF_error,										/*  0: Error token */
	BNF_codeSession,								/*  1 */
	BNF_comment,									/*  2 */
//	BNF_dataSession,								/*  3 */
	BNF_optVarListDeclarations,						/*  4 */
	BNF_optionalStatements,							/*  5 */
	BNF_outputStatement,							/*  6 */
	BNF_outputVariableList,							/*  7 */
	BNF_program,									/*  8 */
	BNF_statement,									/*  9 */
	BNF_statements,									/* 10 */
	BNF_statementsPrime,								/* 11 */
	BNF_selectionStatement,
	BNF_iterationStatement,
	BNF_inputStatement,
	BNF_varDeclarationStatement,
	BNF_assignmentStatement						/* 17 */
};


/* TO_DO: Define the list of keywords */
static string BNFStrTable[NUM_BNF_RULES] = {
	"BNF_error",
	"BNF_codeSession",
	"BNF_comment",
	"BNF_dataSession",
	"BNF_optVarListDeclarations",
	"BNF_optionalStatements",
	"BNF_outputStatement",
	"BNF_outputVariableList",
	"BNF_program",
	"BNF_statement",
	"BNF_statements",
	"BNF_statementsPrime"
};

/* TO_DO: Place ALL non-terminal function declarations */
amber_void codeSession();
amber_void comment();
//amber_void dataSession();
amber_void optVarListDeclarations();
amber_void optionalStatements();
amber_void outputStatement();
amber_void outputVariableList();
amber_void program();
amber_void statement();
amber_void statements();
amber_void statementsPrime();

#endif
