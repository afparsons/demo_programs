/*
COMP 230: Computer Organization
Programming Project 3: Assembler

verifyImmediateIsDecimal()

---SUMMARY---
Check if first char in immediate is a digit.
Check if first char in immediate is '-'.
If neither, return 0 (fail).
Check if remaining characters are digits.
If not, return 0 (fail).
Return 1 (success).

Authors:	Andrew Parsons, Sivhaun Sera
Date:		10 May 2017

Modified: 	12 May 2017, to pass table to getOP()
*/

#include "assembler.h"

int verifyImmediateIsDecimal(char * tokenInArray[])
{
	/* --- handle when immediate is invalid --- */

	int d;																		/* for loop counter */
	int lengthOfImmediate = sizeof(**tokenInArray) / sizeof(tokenInArray[0]);	/* length of string */

	/* check if the first character is a digit, and if it is not, check if it is a negative */
	/* super-micro improvement: keep this independent of the for-loop to reduce number of calculations */
	if (isdigit(*tokenInArray[0]) == 0)
	{
		if (*tokenInArray[0] != '-')
		{
			return 0;
		}
	}


	/* check if the remaining characters are digits */
	for (d = 1; d < lengthOfImmediate; ++d)
	{
		if (isdigit(tokenInArray[d]) == 0)
		{
			return 0;
		}
	}

	return 1;
}
