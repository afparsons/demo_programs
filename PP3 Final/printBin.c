/*
COMP 230: Computer Organization
Programming Project 3: Assembler

This file takes in a dec number and finds its binary number. That bin number is
represented in a char array then printed. if the number is too large to print
in the alloted space an error is prited, and the number is not. if the
number is negitive it is represented in 2's complement sign notation.

Authors:  Andrew Parsons, Sivhaun Sera
Date:   10 May 2017
*/

#include "assembler.h"
#include <math.h>

void printBin (int dec, int length)
{
	int negFlag = 0;
	if (dec < 0)	/* we are dealing with a negitive number */
	{
		dec = dec * -1; /* make it positive */
		negFlag = 1; 	/* flag for negitive */
	}

	if ( pow(2, length-1) - 1 >= dec)
	{
		/* create string of length */
		char output[length];

		/* set null byte */
		output[length-1] = '\0';

		/* convert dec to bin */
		int i;
		for (i = length-2; i >= 0; --i, dec >>= 1)
		{
			output[i] = (dec & 1) + '0';
		}

		/* convert a negative to two's complement if necessary */
		if (negFlag == 1)
		{
			output[0] = '1';
			for (i = 1; i < length-2; i++)
			{
				if (output[i]== '1')
				{
					output[i]='0';
				}

				else
				{
					output[i]='1';
				}
			}
		}

		else /* positive number */
		{
			output[0]='0';
		}

		/* print binary output */
		printf("%s", output);
	}

	else
	{
		printError("\e[93m%s\e[0m\n", "ERROR: decimal doesn't fit into number of bits!");
	}
}
