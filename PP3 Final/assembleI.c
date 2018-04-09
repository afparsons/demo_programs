/*
COMP 230: Computer Organization
Programming Project 3: Assembler

assembleI()

Parses I-format MIPS instructions and calls printBin().
Called by getOP().
If assembly is not possible, prints the appropriate error and line number.
Returns without halting program.

assembleI takes parameters:
char * operation: MIPS instruction
char * tokBegin: pointer to start of instruction
int lineNum: current program counter
int opCode: decimal operation code
LabelTable * table: table of MIPS labels from pass1

assembleI returns:
	0 (failure)
	1 (success)

Authors:	Andrew Parsons, Sivhaun Sera
Date:		10 May 2017
*/

#include "assembler.h"

int assembleI (char * operation, char * tokBegin, int lineNum, int opCode, LabelTable * table)
{

	/* processing variables */
	int n = 4; 								/* number of tokens in MIP */
	int special = 0;						/* special case 'boolean' */
	char * instructionBuffer = tokBegin;	/* skip ahead in the line so we don't include the label */

	/* printing variables */
	int r1;
	int r2;
	int immediate;
	char label[17];
	label[17] = '\0';

	/* set n for the special case of lui*/
	if ( strcmp (operation, "lui") == SAME )
	{
		n = 3;
		special = 1;
	}

	/* create destination for getNTokens tokens */
	char * tokenArray[n];

	/* copy characters starting at tokBegin into string instructionBuffer */
	strcpy(instructionBuffer, tokBegin);

	/* get the non-label tokens for the instructions and store them in the array */
	if ( getNTokens(instructionBuffer, n, tokenArray) == 0)
	{
		/* printError already handled by getNTokens */
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

/* === PRINT THE MIPS === */

	/* --- processing section --- */

	if (special == 1) /* if we are dealing with lui */
	{
		r1 = getRegNbr(*(tokenArray+1));
		r2 = 0;

		if ( verifyImmediateIsDecimal(tokenArray + 3) == 1)
		{
			immediate = atoi(*(tokenArray+3));
		}

		else
		{
			printError("\e[93m%s\e[91m%d\e[0m\n", "ERROR: immediate is not a decimal number! \e[36mline: ", lineNum);
			return 0;
		}
	}
	   			 /* addi ||   addiu 	||     	andi    ||  ori 	*/
	else if (opCode == 8 || opCode == 9 || opCode == 12 || opCode == 13)
	{
		r1 = getRegNbr(*(tokenArray+2));
		r2 = getRegNbr(*(tokenArray+1));

		if ( verifyImmediateIsDecimal(tokenArray + 3) == 1)
		{
			immediate = atoi(*(tokenArray+3));
		}

		else
		{
			printError("\e[93m%s\e[91m%d\e[0m\n", "ERROR: immediate is not a decimal number! \e[36mline: ", lineNum);
			return 0;
		}
	}
	   	  /*   lw         ||    sw	*/
	else if (opCode == 35 || opCode == 43)
	{
		r1 = getRegNbr(*(tokenArray+3));
		r2 = getRegNbr(*(tokenArray+1));
		if ( verifyImmediateIsDecimal(tokenArray + 2) == 1)
		{
			immediate = atoi(*(tokenArray+2));
		}

		else
		{
			printError("\e[93m%s\e[91m%d\e[0m\n", "ERROR: immediate is not a decimal number! \e[36mline: ", lineNum);
			return 0;
		}
	}

				 /* beq  || 	  bne  */
	else if (opCode == 4 || opCode == 5 )
	{
		r1 = getRegNbr(*(tokenArray+1));
		r2 = getRegNbr(*(tokenArray+2));

		int lineNumOfJump = findLabel(table, *(tokenArray+3));

		if (lineNumOfJump != -1 )
		{
			/* need to find this label in the table and get the line num of where to jump to, then claculate offset */
			immediate = (lineNumOfJump - (lineNum + 4))/4; /* aka offset */
		}

		else
		{
			printError("\e[93m%s\e[91m%d\e[0m\n", "ERROR: label not found! \e[36mline: ", lineNum);
		}
	}

	/* 	    	slti     ||  sltiu	*/
	else if (opCode == 10|| opCode == 11)
	{
		r1 = getRegNbr(*(tokenArray+2));
		r2 = getRegNbr(*(tokenArray+1));

		if ( verifyImmediateIsDecimal(tokenArray + 3) == 1)
		{
			immediate = atoi(*(tokenArray+3));
		}

		else
		{
			printError("\e[93m%s\e[91m%d\e[0m\n", "ERROR: immediate is not a decimal number! \e[36mline: ", lineNum);
			return 0;
		}
	}

	else
	{
		printError("\e[93m%s\e[91m%d\e[0m\n", "ERROR: unrecognized opcode! \e[36mline: ", lineNum);
		return 0; /* failure */
	}

	/* print MIPS order */
	printDebug("\e[2;96m%s%s%s%s\e[0m\n", "opCode   ", "r1      ", "r2      ", "immediate");

	/* print binary MIP */
	/* if debug = on, then decimals are printed and bars are inserted */
	/**/printDebug("\e[32m%-9d%-8d%-8d%d\e[0m\n", opCode, r1, r2, immediate);
	printBin(opCode,7);
	/**/printDebug("\e[34m%s\e[0m", " | ");
	printBin(r1,6);
	/**/printDebug("\e[34m%s\e[0m", " | ");
	printBin(r2,6);
	/**/printDebug("\e[34m%s\e[0m", " | ");
	printBin(immediate,17);

	printf("\n");

	/* good */
	return 1;
}
