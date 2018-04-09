/*
COMP 230: Computer Organization
Programming Project 3: Assembler

getRegNbr()

This class takes in a char array of a register. It then iterates throught the
known registers and looks for a match. if so the decimial value is returned, if
not found an error is printed and -1 is returned.

assembleI returns:
	-1 (failure)
	decimal number (success)

Authors:	Andrew Parsons, Sivhaun Sera
Date:		10 May 2017

*/

#include "assembler.h"

int getRegNbr (char * reg)
{
	/* Create a static (persistent) array of the mnemonic names, each of which is a string (char *). */
	static char * regArray[] = {
		"$zero",
		"$at",
		"$v0","$v1",
		"$a0","$a1","$a2","$a3",
    	"$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7",
    	"$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7",
    	"$t8","$t9",
    	"$k0","$k1",
    	"$gp","$sp","$fp","$ra"
	};

	int regNbr = -1; /* this is impossible */

	int i;
	for (i = 0; i <= 31; ++i)
	{
		if (strcmp (regArray[i],reg) == 0)
		{
			regNbr = i;
			return regNbr;
		}
	}

	printError("\e[93m%s\e[0m\n","ERROR: unknown register!");
	return regNbr; //if here it is -1, fail case.

}
