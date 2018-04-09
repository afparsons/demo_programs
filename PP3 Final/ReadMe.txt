COMP 230: Computer Organization: PP2
Andrew Parsons, and Sivhaun Sera 15 may 2017

Purpose: this program reads in a specified file containing MIPS and
converts them to the assembled (binary) form, i.e. assembling.
In the process of 2 passes it generates a label table, parses out comments, and
breaks the individual lines into the component tokens. From there it gets
the opcode in decimal for the specific command, converts registers to the
appropriate decimal value, reads labels in, calculates offset, then converts
all these to binary.

Error Handling:
When the program encounters a MIPS it does not recognize, another type of
input it cannot parse, an unfound label, or something else unexpected like a
register where there should be a decimal the program reports that problem
and line number to printError and moves to the next line.

sample input could look like:
add  $at, $v1, $v0

producing output:
00000000010000110000100000100000

USAGE:

From this file's parent directory:

$ make
$ ./assembler pp3TestCases.txt (or a file of your choosing containing MIPS)
