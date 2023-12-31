﻿/*
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
* File name: Parser.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A32.
* Date: May 01 2023
* Purpose: This file contains all functionalities from Parser.
* Function list: (...).
************************************************************
*/

/* TO_DO: Adjust the function header */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef PARSER_H_
#include "Parser.h"
#endif

/* Parser data */
extern ParserData psData; /* BNF statistics */

/*
************************************************************
 * Process Parser
 ***********************************************************
 */
/* TO_DO: This is the function to start the parser - check your program definition */

amber_void startParser() {
	/* TO_DO: Initialize Parser data */
	int32 i = 0;
	for (i = 0; i < NUM_BNF_RULES; i++) {
		psData.parsHistogram[i] = 0;
	}
	/* Proceed parser */
	lookahead = tokenizer();
	if (lookahead.code != SEOF_T) {
		program();
	}
	matchToken(SEOF_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Source file parsed");
}


/*
 ************************************************************
 * Match Token
 ***********************************************************
 */
/* TO_DO: This is the main code for match - check your definition */
amber_void matchToken(int32 tokenCode, int32 tokenAttribute) {
	int32 matchFlag = 1;
	switch (lookahead.code) {
	case KW_T:
		if (lookahead.attribute.codeType != tokenAttribute)
			matchFlag = 0;
	default:
		if (lookahead.code != tokenCode)
			matchFlag = 0;
	}
	if (matchFlag && lookahead.code == SEOF_T)
		return;
	if (matchFlag) {
		lookahead = tokenizer();
		if (lookahead.code == ERR_T) {
			printError();
			lookahead = tokenizer();
			syntaxErrorNumber++;
		}
	}
	else
		syncErrorHandler(tokenCode);
}

/*
 ************************************************************
 * Syncronize Error Handler
 ***********************************************************
 */
/* TO_DO: This is the function to handler error - adjust basically datatypes */
amber_void syncErrorHandler(int32 syncTokenCode) {
	printError();
	syntaxErrorNumber++;
	while (lookahead.code != syncTokenCode) {
		if (lookahead.code == SEOF_T)
			exit(syntaxErrorNumber);
		lookahead = tokenizer();
	}
	if (lookahead.code != SEOF_T)
		lookahead = tokenizer();
}

/*
 ************************************************************
 * Print Error
 ***********************************************************
 */
/* TO_DO: This is the function to error printing - adjust basically datatypes */
amber_void printError() {
	extern numParserErrors;			/* link to number of errors (defined in Parser.h) */
	Token t = lookahead;
	printf("%s%s%3d\n", STR_LANGNAME, ": Syntax error:  Line:", line);
	printf("*****  Token code:%3d Attribute: ", t.code);
	switch (t.code) {
	case ERR_T:
		printf("*ERROR*: %s\n", t.attribute.errLexeme);
		break;
	case SEOF_T:
		printf("SEOF_T\t\t%d\t\n", t.attribute.seofType);
		break;
	case MNID_T:
		printf("MNID_T:\t\t%s\t\n", t.attribute.idLexeme);
		break;
	case STR_T:
		printf("STR_T: %s\n", readerGetContent(stringLiteralTable, t.attribute.contentString));
		break;
	case KW_T:
		printf("KW_T: %s\n", keywordTable[t.attribute.codeType]);
		break;
	case LPR_T:
		printf("LPR_T\n");
		break;
	case RPR_T:
		printf("RPR_T\n");
		break;
	case LBR_T:
		printf("LBR_T\n");
		break;
	case RBR_T:
		printf("RBR_T\n");
		break;
	case EOS_T:
		printf("NA\n");
		break;
	default:
		printf("%s%s%d\n", STR_LANGNAME, ": Scanner error: invalid token code: ", t.code);
		numParserErrors++; // Updated parser error
	}
}

/*
 ************************************************************
 * Program statement
 * BNF: <program> -> main& { <opt_statements> }
 * FIRST(<program>)= {CMT_T, MNID_T (main&), SEOF_T}.
 ***********************************************************
 */
amber_void program() {
	/* Update program statistics */
	psData.parsHistogram[BNF_program]++;
	/* Program code */
	switch (lookahead.code) {
	case CMT_T:
		comment();
	case MNID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_MAIN, 5) == 0) {
			matchToken(MNID_T, NO_ATTR);
			matchToken(LBR_T, NO_ATTR);
			//dataSession();
			codeSession();
			matchToken(RBR_T, NO_ATTR);
			break;
		}
		else {
			printError();
		}
	case SEOF_T:
		; // Empty
		break;
	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Program parsed");
}

/*
 ************************************************************
 * comment
 * BNF: comment
 * FIRST(<comment>)= {CMT_T}.
 ***********************************************************
 */
amber_void comment() {
	psData.parsHistogram[BNF_comment]++;
	matchToken(CMT_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Comment parsed");
}

/*
 ************************************************************
 * dataSession
 * BNF: <dataSession> -> data { <opt_varlist_declarations> }
 * FIRST(<program>)= {KW_T (KW_data)}.
 ***********************************************************
 */
/*
amber_void dataSession() {
	psData.parsHistogram[BNF_dataSession]++;
	switch (lookahead.code) {
	case CMT_T:
		comment();
	default:
		matchToken(KW_T, KW_var);
		matchToken(LBR_T, NO_ATTR);
		optVarListDeclarations();
		matchToken(RBR_T, NO_ATTR);
		printf("%s%s\n", STR_LANGNAME, ": Data Session parsed");
	}
}
*/

/*
 ************************************************************
 * Optional Var List Declarations
 * BNF: <opt_varlist_declarations> -> <varlist_declarations> | e
 * FIRST(<opt_varlist_declarations>) = { e, KW_T (KW_int), KW_T (KW_real), KW_T (KW_string)}.
 ***********************************************************
 */
amber_void optVarListDeclarations() {
	psData.parsHistogram[BNF_optVarListDeclarations]++;
	switch (lookahead.code) {
	default:
		; // Empty
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional Variable List Declarations parsed");
}

/*
 ************************************************************
 * codeSession statement
 * BNF: <codeSession> -> code { <opt_statements> }
 * FIRST(<codeSession>)= {KW_T (KW_code)}.
 ***********************************************************
 */
amber_void codeSession() {
	psData.parsHistogram[BNF_codeSession]++;
	switch (lookahead.code) {
	case CMT_T:
		comment();
	default:
		//matchToken(KW_T, KW_code);
		matchToken(LBR_T, NO_ATTR);
		optionalStatements();
		matchToken(RBR_T, NO_ATTR);
		printf("%s%s\n", STR_LANGNAME, ": Code Session parsed");
	}
}

/* TO_DO: Continue the development (all non-terminal functions) */

/*
 ************************************************************
 * Optional statement
 * BNF: <opt_statements> -> <statements> | ϵ
 * FIRST(<opt_statements>) = { ϵ , IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *				KW_T(KW_while), MNID_T(print&), MNID_T(input&) }
 ***********************************************************
 */
amber_void optionalStatements() {
	psData.parsHistogram[BNF_optionalStatements]++;
	switch (lookahead.code) {
	case CMT_T:
		comment();
	case MNID_T:
		if ((strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) ||
			(strncmp(lookahead.attribute.idLexeme, LANG_READ, 6) == 0)) {
			statements();
			break;
		}
	default:
		; // Empty
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional statements parsed");
}

/*
 ************************************************************
 * Statements
 * BNF: <statements> -> <statement><statementsPrime>
 * FIRST(<statements>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *		KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
amber_void statements() {
	psData.parsHistogram[BNF_statements]++;
	statement();
	statementsPrime();
	printf("%s%s\n", STR_LANGNAME, ": Statements parsed");
}

/*
 ************************************************************
 * Statements Prime
 * BNF: <statementsPrime> -> <statement><statementsPrime> | ϵ
 * FIRST(<statementsPrime>) = { ϵ , IVID_T, FVID_T, SVID_T, 
 *		KW_T(KW_if), KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
amber_void statementsPrime() {
	psData.parsHistogram[BNF_statementsPrime]++;
	switch (lookahead.code) {
	case CMT_T:
	statements();
	break;
	case MNID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) {
			statements();
			break;
		}
		else if (strncmp(lookahead.attribute.idLexeme, LANG_READ, 6) == 0) {
			statements();
		}
		break;
	case KW_T:
		statements();
		break;
	case VID_T:
		statements();
		break;
	default:
		; //empty string
	}
}

/*
 ************************************************************
 * Single statement
 * BNF: <statement> -> <assignment statement> | <selection statement> |
 *	<iteration statement> | <input statement> | <output statement>
 * FIRST(<statement>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if), KW_T(KW_while),
 *			MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
amber_void statement() {
	psData.parsHistogram[BNF_statement]++;
	switch (lookahead.code) {
	case CMT_T:
		comment();
		break;
	case KW_T:
		switch (lookahead.attribute.codeType) {
		case 5: // if 
			selectionStatement();
			break;
		case 11: // for 
			iterationStatement();
			break;
		case 7: // var
			matchToken(KW_T, KW_var);
			//matchToken(VID_T, NO_ATTR);
			switch (lookahead.attribute.codeType) {
			case 2: // int
			case 3: // float64
			case 4: // string
				varDeclarationStatement();
			}
		default:
			printError();
		}
		break;
	case MNID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) {
			outputStatement();
		}
		else if (strncmp(lookahead.attribute.idLexeme, LANG_READ, 6) == 0) {
			inputStatement();
		}
		break;
	case VID_T:
		printf("VID = %s\n", lookahead.attribute.idLexeme);
		matchToken(VID_T, NO_ATTR);
		matchToken(ASN_T, NO_ATTR);
		assignmentStatement();
		break;
	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Statement parsed");
}

/*
 ************************************************************
 * Output Statement
 * BNF: <output statement> -> print& (<output statementPrime>);
 * FIRST(<output statement>) = { MNID_T(print&) }
 ***********************************************************
 */
amber_void outputStatement() {
	psData.parsHistogram[BNF_outputStatement]++;
	matchToken(MNID_T, NO_ATTR);
	matchToken(LPR_T, NO_ATTR);
	outputVariableList();
	matchToken(RPR_T, NO_ATTR);
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Output statement parsed");
}

/*
 ************************************************************
 * Declaration Statement
 * BNF: <selection statement> -> fmt.Println (<output statementPrime>);
 * FIRST(<output statement>) = { MNID_T(print&) }
 ***********************************************************
 */
void varDeclarationStatement() {
	psData.parsHistogram[BNF_varDeclarationStatement]++;
	switch (lookahead.code) {
	case KW_T:
		if (lookahead.attribute.codeType == 2) { //int
			matchToken(KW_T, KW_int32);
		}
		else if (lookahead.attribute.codeType == 4) { // string
			matchToken(KW_T, KW_string);
		}
		else if (lookahead.attribute.codeType == 3) { //float
			matchToken(KW_T, KW_float32);
		}
		else {
			printError();  // Handle the error case
		}
		break;
	default:
		printError();  // Handle the error case
	}
	printf("%s%s\n", STR_LANGNAME, ": Declaration statement parsed");
}

/*
 ************************************************************
 * Assignment  Statement
 * BNF: <selection statement> -> fmt.Println (<output statementPrime>);
 * FIRST(<output statement>) = { MNID_T(print&) }
 ***********************************************************
 */
void assignmentStatement() {
	psData.parsHistogram[BNF_assignmentStatement]++;
	expression();
	outputVariableList();
	printf("%s%s\n", STR_LANGNAME, ": Assignment statement parsed");
}

/*
 ************************************************************
 * Output Variable List
 * BNF: <opt_variable list> -> <variable list> | ϵ
 * FIRST(<opt_variable_list>) = { IVID_T, FVID_T, SVID_T, ϵ }
 ***********************************************************
 */
amber_void outputVariableList() {
	psData.parsHistogram[BNF_outputVariableList]++;
	switch (lookahead.code) {
	case STR_T:
		matchToken(STR_T, NO_ATTR);
		break;
	case INL_T:  // start of my code
		matchToken(INL_T, NO_ATTR);
		break;
	//case FPL_T:
	//	matchToken(FPL_T, NO_ATTR);
	//	break;
	case VID_T:
		matchToken(VID_T, NO_ATTR);
		break; //end of my code
	default:
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": Output variable list parsed");
}

/*
 ************************************************************
 * The function prints statistics of BNF rules
 * Param:
 *	- Parser data
 * Return:
 *	- Void (procedure)
 ***********************************************************
 */
/*
amber_void printBNFData(ParserData psData) {
}
*/
amber_void printBNFData(ParserData psData) {
	/* Print Parser statistics */
	printf("Statistics:\n");
	printf("----------------------------------\n");
	int cont = 0;
	for (cont = 0; cont < NUM_BNF_RULES; cont++) {
		if (psData.parsHistogram[cont] > 0)
			printf("%s%s%s%d%s", "Token[", BNFStrTable[cont], "]=", psData.parsHistogram[cont], "\n");
	}
	printf("----------------------------------\n");
}

void selectionStatement() {
	psData.parsHistogram[BNF_selectionStatement]++;
	matchToken(KW_T, KW_if);
	matchToken(LPR_T, NO_ATTR);
	condition(); //parametes
	matchToken(RPR_T, NO_ATTR);
	matchToken(LBR_T, NO_ATTR);
	statements();// more code
	matchToken(RBR_T, NO_ATTR);
	matchToken(KW_T, KW_else);
	matchToken(LBR_T, NO_ATTR);
	statements();// more code
	matchToken(RBR_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Selection statement parsed");
}

void condition() {
	expression();
	matchToken(REL_T, NO_ATTR);
	expression();
}

// Function to parse and validate an expression
void expression() {
	if (lookahead.code == LPR_T) {
		matchToken(LPR_T, NO_ATTR);
		expression();
		matchToken(RPR_T, NO_ATTR);
	}
	else {
		term();
		while (lookahead.code == ART_T || lookahead.code == LOG_T) {
			if (lookahead.code == ART_T) {
				matchToken(ART_T, NO_ATTR);
				term();
			}
			else if (lookahead.code == LOG_T) {
				matchToken(LOG_T, NO_ATTR);
				term();
			}
			else if (lookahead.code == LPR_T) {
				matchToken(LPR_T, NO_ATTR);
				expression();
				matchToken(RPR_T, NO_ATTR);
			}
			else {
				printError();
			}
		}
	}
}

// Function to parse and validate a factor
void term() {
	switch (lookahead.code) {
	case VID_T:
		matchToken(lookahead.code, NO_ATTR);
		break;
	case INL_T:
	case FPL_T:
	case STR_T:
		matchToken(lookahead.code, NO_ATTR);
		break;
	default:
		printError();
	}
}
/*
 ************************************************************
 * Selection Statement
 * BNF: <selection statement> -> fmt.Println (<output statementPrime>);
 * FIRST(<output statement>) = { MNID_T(print&) }
 ***********************************************************
 */
void iterationStatement() {
	psData.parsHistogram[BNF_iterationStatement]++;
	matchToken(KW_T, KW_for);
	condition();// condition
	matchToken(LBR_T, NO_ATTR);
	statements();// more code
	matchToken(RBR_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Iteration statement parsed");
}

/*
 ************************************************************
 * Input Statement
 * BNF: <selection statement> -> fmt.Println (<output statementPrime>);
 * FIRST(<output statement>) = { MNID_T(fmt.SCAN&) }
 ***********************************************************
 */
void inputStatement() {
	psData.parsHistogram[BNF_inputStatement]++;
	matchToken(MNID_T, NO_ATTR);
	matchToken(LPR_T, NO_ATTR);
	outputVariableList();
	matchToken(RPR_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Input statement parsed");
}