/*
 * This file includes common system header files, several local header
 * files widely used in the assembler program, and signatures for other
 * commonly used functions.
 */

#ifndef _ASSEMBLER_H
#define _ASSEMBLER_H

#include <stdio.h>
#include <stdlib.h>     /* May need to be _stdlib.h on some machines. */
#include <string.h>	    /* Might be memory.h on some machines. */
#include <ctype.h>

#include "LabelTable.h"
#include "getToken.h"
#include "printFuncs.h"

int getNTokens (char * instructionBuffer, int N, char * results[]);
LabelTable pass1 (FILE * fp);
void pass2 (FILE * ptr_file, LabelTable table);

int assembleR (char * operation, char * tokBegin, int linenum);
int assembleJ (char * operation, char * tokBegin, int lineNum, int opCode, LabelTable * table);
int assembleI (char * operation, char * tokBegin, int lineNum, int opCode, LabelTable * table);
int getOP ( char * operation, char * inst, int lineNum, LabelTable * table);

void printBin (int dec, int length);
int getRegNbr (char * reg);
int verifyImmediateIsDecimal(char * tokenInArray[]);
extern const int SAME;		/* useful for making strcmp readable. e.g., if (strcmp (str1, str2) == SAME) */

#endif
