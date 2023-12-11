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
* File name: Scanner.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A22, A32.
* Date: May 01 2022
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define MNID_LEN 40 /* method identifier length */
#define VID_LEN 20  /* variable identifier length */
#define ERR_LEN 40  /* error message length */
#define NUM_LEN 5   /* maximum number of digits for IL */
#define RTE_CODE 1  /* Value for run-time error */

/* TO_DO: Define the number of tokens */
#define NUM_TOKENS 18

/* TO_DO: Define Token codes - Create your token classes */
enum TOKENS {
	ERR_T,		/*  0: Error token */
	MNID_T,		/*  1: Method name identifier token (start: &) */
	INL_T,		/*  2: Integer literal token */
	FPL_T,
	STR_T,		/*  3: String literal token */
	LPR_T,		/*  4: Left parenthesis token */
	RPR_T,		/*  5: Right parenthesis token */
	LBR_T,		/*  6: Left brace token */
	RBR_T,		/*  7: Right brace token */
	KW_T,		/*  8: Keyword token */
	EOS_T,		/*  9: End of statement (semicolon) */
	RTE_T,		/* 10: Run-time error token */
	SEOF_T,		/* 11: Source end-of-file token */
	CMT_T,		/* 12: Comment token */
	VID_T,		/* 13. Star for comment*/
	REL_T,		/* 14. Star for comment*/
	ASN_T,		/* 15. Star for comment*/
	ART_T		/* 16. Star for comment*/
	
};

/* TO_DO: Define the list of keywords */
static string tokenStrTable[NUM_TOKENS] = {
	"ERR_T",
	"MNID_T",
	"INL_T",
	"FPL_T",
	"STR_T",
	"LPR_T",
	"RPR_T",
	"LBR_T",
	"RBR_T",
	"KW_T",
	"EOS_T",
	"RTE_T",
	"SEOF_T",
	"CMT_T",
	"VID_T",
	"REL_T",
	"ASN_T",
	"ART_T",
	//"STAR_T"
};

/* TO_DO: Operators token attributes */
typedef enum ArithmeticOperators { OP_ADD, OP_SUB, OP_MUL, OP_DIV } AriOperator;
typedef enum RelationalOperators { OP_EQ, OP_NE, OP_GT, OP_LT } RelOperator;
typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT } LogOperator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_255 } EofOperator;

/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	int32 codeType;      /* integer attributes accessor */
	AriOperator arithmeticOperator;		/* arithmetic operator attribute code */
	RelOperator relationalOperator;		/* relational operator attribute code */
	LogOperator logicalOperator;		/* logical operator attribute code */
	EofOperator seofType;				/* source-end-of-file attribute code */
	int32 intValue;				/* integer literal attribute (value) */
	int32 keywordIndex;			/* keyword index in the keyword table */
	int32 contentString;			/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	float floatValue;				/* floating-point literal attribute (value) */
	rune idLexeme[VID_LEN + 1];	/* variable identifier token attribute */
	rune errLexeme[ERR_LEN + 1];	/* error token attribite */
} TokenAttribute;

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct idAttibutes {
	byte flags;			/* Flags information */
	union {
		int32 intValue;				/* Integer value */
		float floatValue;			/* Float value */
		string stringContent;		/* String value */
	} values;
} IdAttibutes;

/* Token declaration */
typedef struct Token {
	int32 code;				/* token code */
	TokenAttribute attribute;	/* token attribute */
	IdAttibutes   idAttribute;	/* not used in this scanner implementation - for further use */
} Token;

/* Scanner */
typedef struct scannerData {
	int32 scanHistogram[NUM_TOKENS];	/* Statistics of chars */
} ScannerData, * pScanData;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF

/*  Special case tokens processed separately one by one in the token-driven part of the scanner:
 *  LPR_T, RPR_T, LBR_T, RBR_T, EOS_T, SEOF_T and special chars used for tokenis include _, & and ' */

/* TO_DO: Define lexeme FIXED classes */
/* These constants will be used on nextClass */
//#define CHRCOL2 '_'
#define CHRCOL2 '*'
//#define CHRCOL3 '&'
#define CHRCOL3 '.'
#define CHRCOL4 '"'
#define CHRCOL6 '\\'
//#define CHRCOL7 ''

/* These constants will be used on VID / MID function */
#define MNID_SUF ')'
#define COMM_SYM '#'

/* TO_DO: Error states and illegal state */
#define ESNR	8		/* Error state with no retract */
#define ESWR	9		/* Error state with retract */
#define FS		10		/* Illegal state */

 /* TO_DO: State transition table definition */
#define NUM_STATES		10
#define CHAR_CLASSES	8

/* TO_DO: Transition table - type of states defined in separate table */
static int32 transitionTable[NUM_STATES][CHAR_CLASSES] = {
/*    [A-z], [0-9],    //,    *,      .,   /',  other SEOF
	   L(0),  D(1),  S(2),  T(3),  P(4), Q(5), O(6)   O(7) */
	{     1,  ESNR,   6,    ESNR,   4 ,  4,   ESNR,  ESWR },	// S0: NOAS
	{     1,    3,    1,    ESNR,	  1,  1,   2,      3   },	// S1: NOAS
	{    FS,   FS,   FS,     FS,     FS,  FS,  FS,	  FS   },	// S2: ASNR (MVID)
	{    FS,   FS,   FS,     FS,     FS,  FS,  FS,	  FS   },	// S3: ASWR (KEY)
	{     4,    4,    4,      4,      5,   4,  4,	  ESWR    },	// S4: NOAS
	{    FS,   FS,   FS,     FS,     FS,  FS,  FS,	  FS   },	// S5: ASNR (SL)
	{     6,    6,    6,      7,      6,   6,  6,	  ESWR   },	// S6: NOAS
	{     7,    7,    7,      8,      7,   7,  7,	  FS   },	// S7: ASNR (COM)
	{     7,    7,    9,      7,      7,   7,  7,      FS   },	// S8: ASNR (ES)
	{    FS,   FS,   FS,     FS,     FS,  FS,  FS,     FS  }  // S9: FSNR (ER)
};

/* Define accepting states types */
#define NOFS	0		/* not accepting state */
#define FSNR	1		/* accepting state with no retract */
#define FSWR	2		/* accepting state with retract */

/* TO_DO: Define list of acceptable states */
static int32 stateType[NUM_STATES] = {
	NOFS, /* 00 */
	NOFS, /* 01 */
	FSNR, /* 02 (MID) - Methods */
	FSWR, /* 03 (KEY) */
	NOFS, /* 04 */
	FSNR, /* 05 (SL) */
	NOFS, /* 06 */
	FSNR, /* 07 (COM) */
	FSNR, /* 08 (Err1 - no retract) */
	FSWR  /* 09 (Err2 - retract) */
};

/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
int32			startScanner(BufferPointer psc_buf);
static int32	nextClass(rune c);					/* character class function */
static int32	nextState(int32, rune);		/* state machine function */
amber_void			printScannerData(ScannerData scData);
Token				tokenizer(amber_void);

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(string lexeme);

/* Declare accepting states functions */
Token funcSL	(string lexeme);
Token funcIL	(string lexeme);
Token funcID	(string lexeme);
Token funcCMT   (string lexeme);
Token funcKEY	(string lexeme);
Token funcErr	(string lexeme);

/* 
 * Accepting function (action) callback table (array) definition 
 * If you do not want to use the typedef, the equvalent declaration is:
 */

/* TO_DO: Define final state table */
static PTR_ACCFUN finalStateTable[NUM_STATES] = {
	NULL,		/* -    [00] */
	NULL,		/* -    [01] */
	funcID,		/* MNID	[02] */
	funcKEY,	/* KEY  [03] */
	NULL,		/* -    [04] */
	funcSL,		/* SL   [05] */
	NULL,		/* -    [06] */
	funcCMT,	/* COM  [07] */
	funcErr,	/* ERR1 [06] */
	funcErr		/* ERR2 [07] */
};

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO: Define the number of Keywords from the language */
#define KWT_SIZE 14

/* TO_DO: Define the list of keywords */
static string keywordTable[KWT_SIZE] = {
	"var",			/* KW00 */
	"int32",		/* KW01 */
	"float32",		/* KW02 */
	"string",		/* KW03 */
	"if",			/* KW04 */
	"then",			/* KW05 */
	"else",			/* KW06 */
	"package",		/* KW07 */
	"import",		/* KW08 */
	"main",			/* KW09 */
	"for",			/* KW10 */
	"func",			/* KW11 */
	"fmt.Println",	/* KW12 */
	"fmt.Scanln"	/* KW13 */
};

/* NEW SECTION: About indentation */

/*
 * Scanner attributes to be used (ex: including: intendation data
 */

#define INDENT '\t'  /* Tabulation */

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct languageAttributes {
	rune indentationCharType;
	int32 indentationCurrentPos;
	/* TO_DO: Include any extra attribute to be used in your scanner (OPTIONAL and FREE) */
} LanguageAttributes;

/* Number of errors */
int32 numScannerErrors;

/* Scanner data */
ScannerData scData;

#endif
