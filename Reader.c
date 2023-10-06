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
***********************************************************
* File name: Reader.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012, 013]
* Assignment: A12.
* Date: May 01 2023
* Professor: Paulo Sousa
* Purpose: This file is the main code for Buffer/Reader (A12)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * - Please check the "TODO" labels to develop your activity.
 * - Review the functions to use "Defensive Programming".
 *.............................................................................
 */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

/*
***********************************************************
* Function name: readerCreate
* Purpose: Creates the buffer reader according to capacity, increment
	factor and operational mode ('f', 'a', 'm')
* Author: Philogene Villanueva, Tasfia Khan Aohana
* History/Versions: S22
* Called functions: calloc(), malloc()
* Parameters:
*   size = initial capacity
*   increment = increment factor
*   mode = operational mode
* Return value: bPointer (pointer to reader)
* Algorithm: Allocation of memory according to inicial (default) values.
* TODO ......................................................
*	- Adjust datatypes for your LANGUAGE.
*   - Use defensive programming
*	- Check boundary conditions
*	- Check flags.
*************************************************************
*/

BufferPointer readerCreate(amber_intg size, amber_intg increment, amber_intg mode) {
	BufferPointer readerPointer;
	/* TO_DO: Defensive programming */

	if(size != 0 || size <= 0){	
		size = READER_DEFAULT_SIZE;
	}

	if(!increment){
		increment = READER_DEFAULT_INCREMENT;
	}

	/* TO_DO: Adjust the values according to parameters */

	readerPointer = (BufferPointer)calloc(1, sizeof(Buffer));
	if (!readerPointer)
		return NULL;
	readerPointer->content = (amber_string)malloc(size);
	
	/* TO_DO: Defensive programming */
	if (mode != 'f' && mode != 'a' && mode != 'm') {
		mode = 'f';
	}

	/* TO_DO: Initialize the histogram */
	readerPointer->size = size;
	readerPointer->increment = increment;
	readerPointer->mode = mode;
	
	/* TO_DO: Initialize flags */
	// Question for Prof
	/* TO_DO: The created flag must be signalized as EMP */
	/* NEW: Cleaning the content */

	if (readerPointer->content)
		readerPointer->content[0] = READER_TERMINATOR;
	readerPointer->position.wrte = 0;
	readerPointer->position.mark = 0;
	readerPointer->position.read = 0;
	return readerPointer;
}


/*
***********************************************************
* Function name: readerAddChar
* Purpose: Adds a char to buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   ch = char to be added
* Return value:
*	readerPointer (pointer to Buffer Reader)
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/

BufferPointer readerAddChar(BufferPointer const readerPointer, amber_char ch) {
	amber_string tempReader = NULL;
	amber_intg newSize = 0;
	/* Defensive programming */
	if (ch > NCHAR || ch < 0) {
		readerPointer->numReaderErrors++;
		return NULL;
	}
	if (!readerPointer) {
		return NULL;
	}
	/* TO_DO: Reset Realocation */
	/* TO_DO: Test the inclusion of chars */
	if (readerPointer->position.wrte * (amber_intg)sizeof(amber_char) < readerPointer->size) {
		/* This buffer is NOT full */
		readerPointer->content[readerPointer->position.wrte++] = ch;
		readerPointer->histogram[ch]++;
		return readerPointer;
	} else {
		/* TO_DO: Reset Full flag */
		readerPointer->flags = readerPointer->flags | READER_FLAG_END;
		switch (readerPointer->mode) {
		case MODE_FIXED:
			return NULL;
		case MODE_ADDIT:
			/* Adjust new size */
			newSize = readerPointer->size + readerPointer->increment;
			/* TO_DO: Defensive programming */
			break;
		case MODE_MULTI:
			/* Adjust new size */
			newSize = readerPointer->size * readerPointer->increment;
			/* TO_DO: Defensive programming */
			break;
		default:
			readerPointer->numReaderErrors++;
			return NULL;
		}
		/* New reader allocation */
		tempReader = (amber_string)realloc(readerPointer->content, newSize);
		/* Defensive programming */
		if (!tempReader) {
			readerPointer->numReaderErrors++;
			return NULL;
		}
		/* TO_DO: Check Relocation */
		readerPointer->content = tempReader;
		readerPointer->size = newSize;
	}
	/* TO_DO: Add the char */
	readerPointer->content[readerPointer->position.wrte++] = ch;
	/* TO_DO: Updates histogram */
	readerPointer->histogram[ch]++;
	return readerPointer;
}

/*
***********************************************************
* Function name: readerClear
* Purpose: Clears the buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
amber_boln readerClear(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if(!readerPointer){
		return AMBER_FALSE;
	}

	//Ask Prof tom
	/* TO_DO: Adjust flags original */
	readerPointer->position.wrte = readerPointer->position.mark = readerPointer->position.read = 0;
	return AMBER_TRUE;
}

/*
***********************************************************
* Function name: readerFree
* Purpose: Releases the buffer address
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
amber_boln readerFree(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */

	if(!readerPointer){
		return AMBER_FALSE;
	}
	/* TO_DO: Free pointers */
	free(readerPointer);

	return AMBER_TRUE;
}

/*
***********************************************************
* Function name: readerIsFull
* Purpose: Checks if buffer reader is full
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
amber_boln readerIsFull(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */

	if(!readerPointer){
		return NULL;
	}
	/* TO_DO: Check flag if buffer is FUL */
	if(readerPointer == READER_FLAG_END){
		return AMBER_TRUE;
	}

	return AMBER_FALSE;
}


/*
***********************************************************
* Function name: readerIsEmpty
* Purpose: Checks if buffer reader is empty.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
amber_boln readerIsEmpty(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */

	if(!readerPointer){
		return NULL;
	}

	if(readerPointer == READER_FLAG_EMP){
		return AMBER_TRUE;
	}

	/* TO_DO: Check flag if buffer is EMP */
	return AMBER_FALSE;
}

/*
***********************************************************
* Function name: readerSetMark
* Purpose: Adjust the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   mark = mark position for char
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
amber_boln readerSetMark(BufferPointer const readerPointer, amber_intg mark) {
	
	if (readerPointer == NULL) {
        /* Check if readerPointer is NULL, return an error */
        return AMBER_FALSE;
    }

    if (mark < 0 || mark > readerPointer->position.wrte) {
        /* Check if mark is out of bounds, return an error */
        return AMBER_FALSE;
    }

    /* Set the mark position to the specified value */
    readerPointer->position.mark = mark;
    return AMBER_TRUE;
}


/*
***********************************************************
* Function name: readerPrint
* Purpose: Prints the string in the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars printed.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
amber_intg readerPrint(BufferPointer const readerPointer) {
	amber_intg cont = 0;
	amber_char c;
	/* TO_DO: Defensive programming (including invalid chars) */
	c = readerGetChar(readerPointer);
	/* TO_DO: Check flag if buffer EOB has achieved */
	while (cont < readerPointer->position.wrte) {
		cont++;
		printf("%c", c);
		c = readerGetChar(readerPointer);
	}
	return cont;
}

/*
***********************************************************
* Function name: readerLoad
* Purpose: Loads the string in the buffer with the content of
	an specific file.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   fileDescriptor = pointer to file descriptor
* Return value:
*	Number of chars read and put in buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
amber_intg readerLoad(BufferPointer const readerPointer, FILE* const fileDescriptor) {
	
	  if (readerPointer == NULL || fileDescriptor == NULL) {
        /* Check if readerPointer or fileDescriptor is NULL, return an error */
        return READER_ERROR;
    }

    amber_intg size = 0;
    amber_char c;

    c = (amber_char)fgetc(fileDescriptor);
    while (!feof(fileDescriptor)) {
        if (!readerAddChar(readerPointer, c)) {
            ungetc(c, fileDescriptor);
            return READER_ERROR;
        }
        c = (amber_char)fgetc(fileDescriptor);
        size++;

        /* Check if the buffer is full */
        if (readerIsFull(readerPointer)) {
            /* Return the current size if the buffer is full */
            return size;
        }
    }

    /* Return the total number of characters read and put in the buffer */
    return size;
}


/*
***********************************************************
* Function name: readerRecover
* Purpose: Rewinds the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
amber_boln readerRecover(BufferPointer const readerPointer) {
	   if (readerPointer == NULL) {
        /* Check if readerPointer is NULL, return an error */
        return AMBER_FALSE;
    }

    /* Reset the read position to 0 */
    readerPointer->position.read = 0;
	return AMBER_TRUE;
}


/*
***********************************************************
* Function name: readerRetract
* Purpose: Retracts the buffer to put back the char in buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
amber_boln readerRetract(BufferPointer const readerPointer) {
	if (readerPointer == NULL) {
        /* Check if readerPointer is NULL, return an error */
        return AMBER_FALSE;
    }

    if (readerPointer->position.read > 0) {
        /* Retract (move back 1 position in read) */
        readerPointer->position.read--;
        return AMBER_TRUE;
    }

    /* Return false if already at the beginning of the buffer */
    return AMBER_FALSE;
}


/*
***********************************************************
* Function name: readerRestore
* Purpose: Resets the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
amber_boln readerRestore(BufferPointer const readerPointer) {
	if (readerPointer == NULL) {
        /* Check if readerPointer is NULL, return an error */
        return AMBER_FALSE;
    }

    /* Set the read position to the mark position */
    readerPointer->position.read = readerPointer->position.mark;
    return AMBER_TRUE;
}


/*
***********************************************************
* Function name: readerGetChar
* Purpose: Returns the char in the getC position.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Char in the getC position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
amber_char readerGetChar(BufferPointer const readerPointer) {
	/* Defensive programming */
	if (!readerPointer) {
		return READER_ERROR;
	}
	/* TO_DO: Check condition to read/wrte */
	/* TO_DO: Set EOB flag */
	/* TO_DO: Reset EOB flag */
	if (readerPointer->position.wrte>0)
		return readerPointer->content[readerPointer->position.read++];
	return READER_TERMINATOR;
}


/*
***********************************************************
* Function name: readerGetContent
* Purpose: Returns the pointer to String.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   pos = position to get the pointer
* Return value:
*	Position of string char.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
amber_string readerGetContent(BufferPointer const readerPointer, amber_intg pos) {
	if (readerPointer == NULL || pos < 0 || pos >= readerPointer->position.wrte) {
        /* Check if readerPointer is NULL or if pos is out of bounds, return NULL */
        return NULL;
    }

    /* Return the pointer to the specified position in the content */
    return readerPointer->content + pos;
}



/*
***********************************************************
* Function name: readerGetPosRead
* Purpose: Returns the value of getCPosition.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The read position offset.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
amber_intg readerGetPosRead(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if(readerPointer == NULL){
		return READER_ERROR;
	}

	/* TO_DO: Return read */
	return readerPointer->position.read;
}


/*
***********************************************************
* Function name: readerGetPosWrte
* Purpose: Returns the position of char to be added
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Write position
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
amber_intg readerGetPosWrte(BufferPointer const readerPointer) {
	 if (readerPointer == NULL) {
        /* Check if readerPointer is NULL, return an error value (e.g., -1) */
        return READER_ERROR;
    }
	
	/* TO_DO: Return wrte */
	 return readerPointer->position.wrte;
}


/*
***********************************************************
* Function name: readerGetPosMark
* Purpose: Returns the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Mark position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
amber_intg readerGetPosMark(BufferPointer const readerPointer) {
 	if (readerPointer == NULL) {
        /* Check if readerPointer is NULL, return an error value (e.g., -1) */
        return READER_ERROR;
    }

    /* Return the mark position */
    return readerPointer->position.mark;
}


/*
***********************************************************
* Function name: readerGetSize
* Purpose: Returns the current buffer capacity
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Size of buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
amber_intg readerGetSize(BufferPointer const readerPointer) {
	if (readerPointer == NULL) {
        /* Check if readerPointer is NULL, return an error value (e.g., -1) */
        return READER_ERROR;
    }

    /* Return the current buffer capacity (size) */
    return readerPointer->size;
}

/*
***********************************************************
* Function name: readerGetInc
* Purpose: Returns the buffer increment.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The Buffer increment.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
amber_intg readerGetInc(BufferPointer const readerPointer) {
	 if (readerPointer == NULL) {
        /* Check if readerPointer is NULL, return an error value (e.g., -1) */
        return READER_ERROR;
    }

    /* Return the buffer increment */
    return readerPointer->increment;
}

/*
***********************************************************
* Function name: readerGetMode
* Purpose: Returns the operational mode
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Operational mode.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
amber_intg readerGetMode(BufferPointer const readerPointer) {
	 if (readerPointer == NULL) {
        /* Check if readerPointer is NULL, return an error value (e.g., -1) */
        return READER_ERROR;
    }

    /* Return the operational mode */
    return readerPointer->mode;
}


/*
***********************************************************
* Function name: readerGetFlags
* Purpose: Returns the entire flags of Buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Flags from Buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
amber_byte readerGetFlags(BufferPointer const readerPointer) {
	if (readerPointer == NULL) {
        /* Check if readerPointer is NULL, return an error value (e.g., 0) */
        return 0;
    }

    /* Return the entire flags from Buffer */
    return readerPointer->flags;
}



/*
***********************************************************
* Function name: readerPrintStat
* Purpose: Shows the char statistic.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value: (Void)
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
amber_void readerPrintStat(BufferPointer const readerPointer) {
	/* Defensive programming */
	if (!readerPointer) {
		return;
	}
	/* Print the histogram */
	printf("Histogram:\n");
	for (int i = 0; i < NCHAR; i++) {
		printf("Value %d: %d\n", i, readerPointer->histogram[i]);
	}
}

/*
***********************************************************
* Function name: readerNumErrors
* Purpose: Returns the number of errors found.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of errors.
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
amber_intg readerNumErrors(BufferPointer const readerPointer) {
	/* Defensive programming */
	if (!readerPointer) {
		return READER_ERROR;
	}
	/* Returns the number of errors */
	return readerPointer->numReaderErrors;
}
