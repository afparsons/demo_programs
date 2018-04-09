/*
COMP 230: Computer Organization
Programming Project 3: Assembler

assembleR()

Parses R-format MIPS instructions and calls printBin().
Called by getOP().
If assembly is not possible, prints the appropriate error and line number.
Returns without halting program.

assembleR takes parameters:
char * operation: MIPS instruction
char * tokBegin: pointer to start of instruction
int lineNum: current program counter

assembleR returns:
	0 (failure)
	1 (success)

Authors:	Andrew Parsons, Sivhaun Sera
Date:			13 May 2017
*/

#include "assembler.h"

int assembleR (char * operation, char * tokBegin, int linenum)
{
	/* processing variables */
	int n = 4; /* number of tokens in MIP */
	int special = 0;	/* special case 'boolean' */
	char * instructionBuffer = tokBegin;	/* skip ahead in the line so we don't include the label */

	/* printing variables */
	int opCode = 0;
	int rd;
	int rs;
	int rt;
	int shamt = 0;
	int func;

	/* set n for the special case */
	if ( strcmp (operation, "jr") == SAME )
	{
		n = 2;
		special = 1;
	}

	/* create destination for getNTokens tokens */
	char * tokenArray[n];

	/* copy characters starting at tokBegin into string instructionBuffer */
	strcpy(instructionBuffer, tokBegin);

	/* get the non-label tokens for the instructions and store them in the array */
	if (getNTokens(instructionBuffer, n, tokenArray) == 0) //failed to get correct tok amount
	{
			/* already handled in getNTokens.
			printError("\e[93m%s\e[91m%d %s\e[0m\n ", "ERROR: Unable to get correct amount of tokens for line: ", linenum, tokenArray[0]);
			*/
			return 0;
	}

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

	if (special == 0)
	{
		/* === Set FUNC from first element === */
		/* this isn't elegant, and there's lots of redundant code, but it is 7th week... */

		/* set the register decimal values */
		rd = getRegNbr(*(tokenArray+1));
		rs = getRegNbr(*(tokenArray+2));
		/* rt = getRegNbr(*(tokenArray+3)); */

		/* determine the func code */
		/* unorthodox formatting, but it takes up so much space otherwise... */
		if ( strcmp (*tokenArray, "add") == SAME ){ func = 32; }

		else if ( strcmp (*tokenArray, "addu") == SAME ){ func = 33; rt = getRegNbr(*(tokenArray+3)); }

		else if ( strcmp (*tokenArray, "sub") == SAME ){ func = 34; rt = getRegNbr(*(tokenArray+3)); }

		else if ( strcmp (*tokenArray, "subu") == SAME ){ func = 35; rt = getRegNbr(*(tokenArray+3)); }

		else if ( strcmp (*tokenArray, "and") == SAME ){ func = 36; rt = getRegNbr(*(tokenArray+3)); }

		else if ( strcmp (*tokenArray, "or") == SAME ){ func = 37; rt = getRegNbr(*(tokenArray+3)); }

		else if ( strcmp (*tokenArray, "nor") == SAME ){ func = 39; rt = getRegNbr(*(tokenArray+3)); }

		else if ( strcmp (*tokenArray, "sll") == SAME )
		{
			rd = getRegNbr(*(tokenArray+1));
			rs = 0;
			rt = getRegNbr(*(tokenArray+2));
			shamt = atoi(*(tokenArray+3));
			func = 0;
		}

		else if ( strcmp (*tokenArray, "srl") == SAME )
		{
			rd = getRegNbr(*(tokenArray+1));
			rs = 0;
			rt = getRegNbr(*(tokenArray+2));
			shamt = atoi(*(tokenArray+3));
			func = 2;
		}

		else if ( strcmp (*tokenArray, "slt") == SAME ){ func = 42;	}

		else if ( strcmp (*tokenArray, "sltu") == SAME ){ func = 43; }

		else if ( strcmp (*tokenArray, "jr") == SAME ){ func = 8; }
	}

	else if (special = 1)
	{
		func = 8;
		rs = getRegNbr(*(tokenArray+1));
	}

	if (rs == -1 || rt == -1 || rd == -1 )
	{
		/* if register is not found, return 0 (failure). */
		/* error message already prints. */
		return 0;
	}

	/* print MIPS order */
	printDebug("\e[2;96m%s%s%s%s%s%s\e[0m\n", "opCode   ", "rs      ", "rt      ", "rd      ", "shamt   ", "func");

	/* print binary MIP */
	/* if debug = on, then bars are inserted */
	/**/printDebug("\e[32m%-9d%-8d%-8d%-8d%-8d%d\e[0m\n", opCode, rs, rt, rd, shamt, func);
	printBin(opCode,7);
	/**/printDebug("\e[34m%s\e[0m", " | ");
	printBin(rs,6);
	/**/printDebug("\e[34m%s\e[0m", " | ");
	printBin(rt,6);
	/**/printDebug("\e[34m%s\e[0m", " | ");
	printBin(rd,6);
	/**/printDebug("\e[34m%s\e[0m", " | ");
	printBin(shamt,6);
	/**/printDebug("\e[34m%s\e[0m", " | ");
	printBin(func,7);

	printf("\n");

	/* good */
	return 1;

	/* USEFUL */
	/* https://courses.cs.washington.edu/courses/cse378/09au/lectures/cse378au09-04.pdf */
	/* http://www-inst.eecs.berkeley.edu/~cs61c/resources/MIPS_help.html */
	/* http://alumni.cs.ucr.edu/~vladimir/cs161/mips.html */
	/* http://misc.flogisoft.com/bash/tip_colors_and_formatting */

}
