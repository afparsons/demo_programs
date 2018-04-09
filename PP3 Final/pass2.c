/*
COMP 230: Computer Organization
Programming Project 3: Assembler

Pass 2

Pass 2 parses a MIPS line, getting the operation and sending it to a handler, getOP().

---SUMMARY---
Read in a file, line by line.
Line is checked for a comment. If there is a comment, skip to the next line.
Line is checked for a label. If there is a label, then set the character pointer to the operation token.
Pass pertinent information to getOP().

Authors:	Andrew Parsons, Sivhaun Sera
Date:		10 May 2017

Modified: 	12 May 2017, to pass table to getOP()
*/

#include "assembler.h"

void pass2 (FILE * ptr_file, LabelTable table)
{
	char * tokBegin, * tokEnd;     		/* used to step thru inst */
	int    PC = 0;                 		/* the program counter */
	char   inst[BUFSIZ];           		/* will hold instruction; BUFSIZ is max size of I/O buffer */
	LabelTable * ptr_table = &table;	/* pointer to the passed table */

	/* Continuously read next line of input until EOF is encountered. Check each line to see if it has a label; if it does, add it to the label table.*/
	for (PC = 0; fgets (inst, BUFSIZ, ptr_file); PC += 4)
	{
		/* Get rid of comment at end of line (if any). If the line starts with a comment, move on to next line.*/
		if ( *inst == '#' ) continue;
		(void) strtok (inst, "#");

		/* Skip any leading whitespace. */
		tokBegin = inst;

		/* point tokBegin to 1st non-whitespace character in the token,
		and point tokEnd to 1st punctuation mark or whitespace after the end of the token. */
		getToken (&tokBegin, &tokEnd);

		/* if the first token is a label, then the second is our function */
		if ( *(tokEnd) == ':' )
		{
			tokBegin = tokEnd + 1;
			tokEnd = tokBegin + 1;

			/* skip the label; the line starts at the operation */
			getToken (&tokBegin, &tokEnd);
		}

		int tokenLength = tokEnd - tokBegin;
		char operation[tokenLength+1];
		memset(operation, '\0', sizeof(operation));
		strncpy(operation, tokBegin, tokenLength);

		if (getOP(operation, tokBegin, PC, ptr_table) != 1 )
		{
			printError("\e[93m%s\e[91m%d\e[0m\n","ERROR: Unknown MIP name. \e[36mline: ", PC);
		}
	}
}
