/*
COMP 230: Computer Organization
Programming Project 3: Assembler

getOP()

Calls the proper assembler for a passed operation
If opCode cannot be found, prints the appropriate error and line number.
Returns without halting program.

assembleI takes parameters:
char * operation: MIPS instruction
char * tokBegin: pointer to start of instruction
int lineNum: current program counter
LabelTable * table: table of MIPS labels from pass1

getOP returns:
	0 (failure)
	1 (success)

Authors:	Andrew Parsons, Sivhaun Sera
Date:		12 May 2017

*/

#include "assembler.h"

/* useful for making strcmp readable. e.g., if (strcmp (str1, str2) == SAME) */
/*const int SAME = 0; */

int getOP (char * operation, char * tokBegin, int lineNum, LabelTable * table)
{

	/* direct tokBegin to the proper assembler */

	/* === R types ===*/

	if ( strcmp (operation, "add") == SAME )
	{
		return assembleR (operation, tokBegin, lineNum);
	}

	else if ( strcmp (operation, "addu") == SAME )
	{
		return assembleR (operation, tokBegin, lineNum);
	}

	else if ( strcmp (operation, "sub") == SAME )
	{
		return assembleR (operation, tokBegin, lineNum);
	}

	else if ( strcmp (operation, "subu") == SAME )
	{
		return assembleR (operation, tokBegin, lineNum);
	}

	else if ( strcmp (operation, "and") == SAME )
	{
		return assembleR (operation, tokBegin, lineNum);
	}

	else if ( strcmp (operation, "or") == SAME )
	{
		return assembleR (operation, tokBegin, lineNum);
	}

	else if ( strcmp (operation, "nor") == SAME )
	{
		return assembleR (operation, tokBegin, lineNum);
	}

	else if ( strcmp (operation, "sll") == SAME )
	{
		return assembleR (operation, tokBegin, lineNum);
	}

	else if ( strcmp (operation, "srl") == SAME )
	{
		return assembleR (operation, tokBegin, lineNum);
	}

	else if ( strcmp (operation, "slt") == SAME )
	{
		return assembleR (operation, tokBegin, lineNum);
	}

	else if ( strcmp (operation, "sltu") == SAME )
	{
	 	return assembleR (operation, tokBegin, lineNum);
	}

	else if ( strcmp (operation, "jr") == SAME )
	{
		return assembleR (operation, tokBegin, lineNum);
	}


	/* === I type === */

	else if ( strcmp (operation, "addi") == SAME )
	{
		return assembleI(operation, tokBegin, lineNum, 8, table);
	}

	else if ( strcmp (operation, "addiu") == SAME )
	{
		return assembleI(operation, tokBegin, lineNum, 9, table);
	}

	else if ( strcmp (operation, "andi") == SAME )
	{
		return assembleI(operation, tokBegin, lineNum, 12, table);
	}

	else if ( strcmp (operation, "ori") == SAME )
	{
		return assembleI(operation, tokBegin, lineNum, 13, table);
	}

	else if ( strcmp (operation, "lw") == SAME )
	{
		return assembleI(operation, tokBegin, lineNum, 35, table);
	}

	else if ( strcmp (operation, "sw") == SAME )
	{
		return assembleI(operation, tokBegin, lineNum, 43, table);

	}

	else if ( strcmp (operation, "lui") == SAME )
	{
		return assembleI(operation, tokBegin, lineNum, 15, table);

	}

	else if ( strcmp (operation, "beq") == SAME )
	{
		return assembleI(operation, tokBegin, lineNum, 4, table);

	}

	else if ( strcmp (operation, "bne") == SAME )
	{
		return assembleI(operation, tokBegin, lineNum, 5, table);
	}

	else if ( strcmp (operation, "slti") == SAME)
	{
		return assembleI(operation, tokBegin, lineNum, 10, table);
	}

	else if ( strcmp (operation, "sltiu") == SAME)
	{
		return assembleI(operation, tokBegin, lineNum, 11, table);
	}

	/* === J type === */

	else if ( strcmp (operation, "j") == SAME )
	{
		return assembleJ(operation, tokBegin, lineNum, 2, table);

	}

	else if ( strcmp (operation, "jal") == SAME )
	{
		return assembleJ(operation, tokBegin, lineNum, 3, table);

	}

	else
	{
		printError("\e[93m%s\e[91m%d\e[0m\n","\nERROR: OP not found! \e[36mline: ", lineNum);
		return 0;
	}
}
