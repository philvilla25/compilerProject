/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2023
* Author: Philogene Villanueva, Tasfia Khan Aohana
* Professors: Paulo Sousa
************************************************************
=---------------------------------------=
|  COMPILERS - ALGONQUIN COLLEGE (F23)  |
=---------------------------------------=
|              ....                     |
|          ........::.::::::.           |
|        .:........::.:^^^~~~:          |
|        :^^::::::^^^::^!7??7~^.        |
|       .:^~~^!77777~~7?YY?7??7^.       |
|       :.^~!??!^::::^^~!?5PY??!~.      |
|       ~!!7J~.:::^^^^~!!~~?G5J?~       |
|       :^~?!~7?Y57^^?PP5YJ!J5Y?:       |
|       .~!!.:^!7!:.:7JYYJ7~7Y7^        |
|       .~77..    . .~^:^^^~7?:         |
|       .^!^~:::.:^!7?~^~!77J:          |
|        ^^!Y~^^^^~?YJ77??7JJ^          |
|       .^7J?~^~~^~7??7??7JY?~:         |
|        ::^^~^7?!^~~!7???J?J7~:.       |
|         ^~~!.^7YPPPP5Y?7J7777~.       |
|        ..:~..:^!JPP5YJ?!777!^.        |
| .~?JJJJJJJJJJYYYYYPPPPPPPPPPPP5PPYY~  |
|     A   M   M   BBBBB    EEEEE  RRRR  |
|    / \  MM MM  B     B  E      R   R  |
|   |   | M M M  BBBBB    EEEE   RRRR   |
|   |   | M   M  B     B  E      R  R   |
|   |   | M   M   BBBBB    EEEEE  R   R |
=---------------------------------------=
*/

/*
************************************************************
* File name: Reader.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012]
* Assignment: A12.
* Date: May 01 2023
* Professor: Paulo Sousa
* Purpose: This file is the main header for Reader (.h)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * Please check the "TODO" labels to develop your activity.
 *.............................................................................
 */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#define READER_H_

/* TIP: Do not change pragmas, unless necessary .......................................*/
/*#pragma warning(1:4001) *//*to enforce C89 type comments  - to make //comments an warning */
/*#pragma warning(error:4001)*//* to enforce C89 comments - to make // comments an error */

/* standard header files */
#include <stdio.h>  /* standard input/output */
#include <malloc.h> /* for dynamic memory allocation*/
#include <limits.h> /* implementation-defined data type ranges and limits */

/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT) .................................. */

/* Modes (used to create buffer reader) */
enum READER_MODE {
	MODE_FIXED = 'f', /* Fixed mode (constant size) */
	MODE_ADDIT = 'a', /* Additive mode (constant increment to be added) */
	MODE_MULTI = 'm'  /* Multiplicative mode (constant increment to be multiplied) */
};

/* Constants about controls (not need to change) */
#define READER_ERROR		(-1)						/* General error message */
#define READER_TERMINATOR	'\0'							/* General EOF */

/* CONSTANTS DEFINITION: PREFIXED BY LANGUAGE NAME (amber) .................................. */

/* You should add your own constant definitions here */
#define READER_MAX_SIZE	INT_MAX-1	/* maximum capacity */ 

#define READER_DEFAULT_SIZE			250		/* default initial buffer reader capacity */
#define READER_DEFAULT_INCREMENT	10		/* default increment factor */

/* Add your bit-masks constant definitions here - Defined for BOA */
/* BITS                                (7654.3210) */
#define READER_DEFAULT_FLAG 0x00 	/* (0000.0000)_2 = (000)_10 */
/* TO_DO: BIT 3: END = End of buffer flag */
/* TO_DO: BIT 2: REL = Rellocation memory flag */
/* TO_DO: BIT 1: EMP = Buffer empty flag */
/* TO_DO: BIT 0: FUL = Buffer full flag */

#define NCHAR				128			/* Chars from 0 to 127 */

#define CHARSEOF			(-1)		/* EOF Code for Reader */

/* STRUCTURES DEFINITION: SUFIXED BY LANGUAGE NAME (AMBER) .................................. */

/* TODO: Adjust datatypes */

/* Offset declaration */
typedef struct position {
	amber_intg mark;			/* the offset to the mark position (in chars) */
	amber_intg read;			/* the offset to the get a char position (in chars) */
	amber_intg wrte;			/* the offset to the add chars (in chars) */
} Position;

/* Buffer structure */
typedef struct bufferReader {
	amber_string	content;			/* pointer to the beginning of character array (character buffer) */
	amber_intg		size;				/* current dynamic memory size (in bytes) allocated to character buffer */
	amber_intg		increment;			/* character array increment factor */
	amber_intg		mode;				/* operational mode indicator */
	amber_byte		flags;				/* contains character array reallocation flag and end-of-buffer flag */
	Position		position;				/* Offset / position field */
	amber_intg		histogram[NCHAR];	/* Statistics of chars */
	amber_intg		numReaderErrors;	/* Number of errors from Reader */
} Buffer, *BufferPointer;

/* FUNCTIONS DECLARATION:  .................................. */
/* General Operations */
BufferPointer	readerCreate		(amber_intg, amber_intg, amber_intg);
BufferPointer	readerAddChar		(BufferPointer const, amber_char);
amber_boln		readerClear		    (BufferPointer const);
amber_boln		readerFree		    (BufferPointer const);
amber_boln		readerIsFull		(BufferPointer const);
amber_boln		readerIsEmpty		(BufferPointer const);
amber_boln		readerSetMark		(BufferPointer const, amber_intg);
amber_intg		readerPrint		    (BufferPointer const);
amber_intg		readerLoad			(BufferPointer const, FILE* const);
amber_boln		readerRecover		(BufferPointer const);
amber_boln		readerRetract		(BufferPointer const);
amber_boln		readerRestore		(BufferPointer const);
/* Getters */
amber_char		readerGetChar		(BufferPointer const);
amber_string	readerGetContent	(BufferPointer const, amber_intg);
amber_intg		readerGetPosRead	(BufferPointer const);
amber_intg		readerGetPosWrte	(BufferPointer const);
amber_intg		readerGetPosMark	(BufferPointer const);
amber_intg		readerGetSize		(BufferPointer const);
amber_intg		readerGetInc		(BufferPointer const);
amber_intg		readerGetMode		(BufferPointer const);
amber_byte		readerGetFlags		(BufferPointer const);
amber_void		readerPrintStat		(BufferPointer const);
amber_intg		readerNumErrors		(BufferPointer const);

#endif
