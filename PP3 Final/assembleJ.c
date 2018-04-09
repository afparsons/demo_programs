/*
COMP 230: Computer Organization
Programming Project 3: Assembler

assembleJ()

Parses J-format MIPS instructions and calls printBin().
Called by getOP().
If assembly is not possible, prints the appropriate error and line number.
Returns without halting program.

assembleJ takes parameters:
char * operation: MIPS instruction
char * tokBegin: pointer to start of instruction
int lineNum: current program counter
int opCode: decimal operation code
LabelTable * table: table of MIPS labels from pass1

assembleJ returns:
	0 (failure)
	1 (success)

Authors:	Andrew Parsons, Sivhaun Sera
Date:		10 May 2017
*/

#include "assembler.h"

int assembleJ (char * operation, char * tokBegin, int lineNum, int opCode, LabelTable * table)
{

	/* processing variables */
	int n = 2; 								/* number of tokens in MIP */
	char * instructionBuffer = tokBegin;	/* skip ahead in the line so we don't include the label */
	int immediate;
	int offset; 							/* the offest to print */
	char label[17]; 						/* the label to find */
	label[16] = '\0';

	/* create destination for getNTokens tokens */
	char * tokenArray[n];

	/* copy characters starting at tokBegin into string instructionBuffer */
	strcpy(instructionBuffer, tokBegin);

	/* get the non-label tokens for the instructions and store them in the array */
	getNTokens(instructionBuffer, n, tokenArray);

	/* === PRINT TOKEN ARRAY === */
	/* this is gorgeous to be honest */
	printDebug("\n");

	/* open array bracket */
	printDebug("\e[91m%s\e[0m", "[ ");

	int s; /* save for the end align */
	int i;
	for (i = 0; i < n; ++i)
	{
		/* print the token elements */
		printDebug("\e[44m%s\e[0m", tokenArray[i]);

		/* insert two spaces for legibility */
		if (i < n-1)
		{
			printDebug("  ");
		}
	}


	/* close array bracket */
	printDebug("\e[91m%s\n", " ]");

	/* --- NEXT ROW (indecies) --- */

	/* open array bracket */
	printDebug("\e[91m%s\e[0m", "[ ");

	for (i = 0; i < n; ++i)
	{
		/* print the index */
		printDebug("%d", i);

		/* align the index with the element */
		if (i < n-1)
		{
			int numSpaces = strlen(tokenArray[i]);
			int j;
			for (j = 0; j < numSpaces-1; ++j)
			{
				printDebug(" ");
			}

			printDebug("  ");
		}
		s = i;
	}

	/* align the closing bracket with the other closing bracket */
	int align = strlen(tokenArray[s]) - 1;
	int k;
	for (k = 0; k < align; ++k)
	{
		printDebug(" ");
	}

	/* close array bracket */
	printDebug("\e[91m%s\e[0m\n", " ]");
	/* --- end token array printing --- */

	/* === PRINT THE MIPS!!! === */

	/* need to find this label in the table and get the line num  of where to jump to, then claculate offset */
	int lineNumOfJump =  findLabel(table, *(tokenArray+1));
	if (lineNumOfJump == -1)
	{
		printError("%s%s%s%d", "label (" , *(tokenArray+1) , ") not found for line ", lineNum);
		return 0;
	}
	immediate = ( lineNumOfJump - (lineNum +4))/4; /* aka offset */

	/* print MIPS order */
	printDebug("\e[2;96m%s%s\e[0m\n", "opCode   ", " offset ");

	/* print binary MIP */
	/* if debug = on, then bars are inserted */
	/**/printDebug("\e[32m%-9d%d\e[0m\n", opCode, immediate);
	printBin(opCode,7);
	/**/printDebug("\e[34m%s\e[0m", " | ");
	printBin(immediate,27);
	printf("\n");

	/* good */
	return 1;
}
