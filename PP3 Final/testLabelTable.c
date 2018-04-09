 /*
 * Test Driver to test the functions to access and manipulate a label table.
 * It includes the following tests:
 *
 *      % adding labels to the static table
 *      % searching for static label that doesn't exist
 *      % searching for static labels that do exist, including on the ends
 *      % searching for static labels beyond the table
 *      % searching for an empty label
 *      % adding labels to the dynamic table
 *      % searching for dynamic labels that do exist, including on the ends
 *      % searching for dynamic label that doesn't exist
 *      % searching for an empty label
 *      % creating an uninitialized table
 *
 * Author:  Andrew Parsons
 *
 * Creation Date:  6 April 2017
 */

#include "assembler.h"

const int SAME = 0;		/* useful for making strcmp readable. e.g., if (strcmp (str1, str2) == SAME) */
static int process_debug_choice(int argc, char * argv[]);
static void testSearch(LabelTable * table, char * searchLabel);

int main(int argc, char * argv[]) {

    /* Can turn debugging on or off here (debug_on() or debug_off()) or on the command line (pass 1 for on; 0 for off). */
    process_debug_choice(argc, argv);

    /* Examples of basic boundary testing:
     *   Set nbrLabels to 0 and test.
     *   Put four more entries in staticEntries, set nbrLabels to 5,
     *   and test.
     */

    /* Create tables */
    LabelTable staticLabelTable;       /* will be a table with static entries */
    LabelTable dynamicLabelTable;      /* will be a table with dynamic entries */

    /* Create table pointers */
    LabelTable * ptr_staticLabelTable = &staticLabelTable;
    LabelTable * ptr_dynamicLabelTable = &dynamicLabelTable;

    /* Static table entry array population */
    LabelEntry staticEntries[8];
    staticEntries[0].label = "Static Label 1";
    staticEntries[0].address = 1000;
    staticEntries[1].label = "Static Label 2";
    staticEntries[1].address = 2000;
    staticEntries[2].label = "Static Label 3";
    staticEntries[2].address = 3000;
    staticEntries[3].label = "Static Label 4";
    staticEntries[3].address = 4000;

    /* Initialize staticLabelTable table with a static array of a given size. */
    staticLabelTable.capacity = 8;
    staticLabelTable.nbrLabels = 4;
    staticLabelTable.entries = staticEntries;

    printf("\n%s\n", "\e[1;3m============ORIGINAL STATIC TABLE============\e[0m");

    printLabels(ptr_staticLabelTable);

    printf("\n%s\n", "\e[1;4m============STATIC TABLE TESTING============\e[0m");

    /* Add labels to staticLabelTable */
    staticEntries[4].label = "Static Label 5";
    staticEntries[4].address = 5000;
    staticEntries[5].label = "Static Label 6";
    staticEntries[5].address = 6000;
    staticEntries[6].label = "Static Label 7";
    staticEntries[6].address = 7000;
    staticEntries[7].label = "Static Label 8";
    staticEntries[7].address = 8000;
    staticLabelTable.nbrLabels = 8;

    /* print the new staticLabelTable */
    printLabels(ptr_staticLabelTable);

    /* Find labels */
    testSearch(ptr_staticLabelTable, "Static Label 0");
    testSearch(ptr_staticLabelTable, "Static Label 1");
    testSearch(ptr_staticLabelTable, "Static Label 4");
    testSearch(ptr_staticLabelTable, "Static Label 8");
    testSearch(ptr_staticLabelTable, "Static Label 17");
    testSearch(ptr_staticLabelTable, "");
    testSearch(ptr_staticLabelTable, "Am I here?");

    printf("\n%s\n", "\e[1;4m==========INITIALIZED DYNAMIC TABLE==========\e[0m");

    /* Initialize dynamicLabelTable as a dynamic table. */
    tableInit(&dynamicLabelTable);
    printLabels(ptr_dynamicLabelTable);

    printf("\n%s\n", "\e[1;4m=======ADDING LABELS TO DYNAMIC TABLE=======\e[0m");

    /* Populate dynamicTable with label data */
    int l;
    for ( l = 1; l <= 10; l++)
    {
        char label[10];
        sprintf(label, "Dynamic Label %d", l);
        addLabel(ptr_dynamicLabelTable, label,l*150);
    }

    /* Print the table after populating with data*/
    printLabels(ptr_dynamicLabelTable);

    printf("\n%s\n", "\e[1;4m============DYNAMIC TABLE TESTING============\e[0m");

    /* testSearch the dynamicLabelTable. */
    testSearch(ptr_dynamicLabelTable,"Dynamic Label 1");
    testSearch(ptr_dynamicLabelTable,"Dynamic Label 5");
    testSearch(ptr_dynamicLabelTable,"Dynamic Label 10");
    testSearch(ptr_dynamicLabelTable,"");
    testSearch(ptr_dynamicLabelTable,"This doesn't exist");
    printf("\n");
}

/*
 * The internal (static) process_debug_choice function parses the
 * command-line arguments for an optional choice (1 or 0) to turn all
 * debugging messages on or off.  The arguments passed to
 * process_debug_choice should be the same arguments that were passed to
 * the main function.  If the arguments were valid (no arguments passed,
 * or 0 or 1 passed as only argument), then this function returns 1; it
 * returns 0 if an invalid argument was passed in.
 *
 * A debugging choice argument of 0 or 1 indicates a choice to globally
 * turn debugging off or on, overriding any calls to debug_on,
 * debug_off, and debug_restore in the code.  0 means that no debugging
 * messages should be printed, 1 means that all debugging messages
 * should be printed.  If no debugging choice is specified, the
 * debug_print function will either print or not print messages
 * depending on the current debugging state set by the debug_on,
 * debug_off, and debug_restore functions.
 */
static int process_debug_choice(int argc, char * argv[])
{
    /* Process debugging choice and then decrement the argument count. */
    if ( argc > 1 )
    {
        if ( strcmp(argv[1], "0") == SAME )
        {
            debug_off();  override_debug_changes();
            argc--;
        }
        else if ( strcmp(argv[1], "1") == SAME )
        {
            debug_on();  override_debug_changes();
            argc--;
        }
    }

    /* The argument count should now be 1, either because there were no
     * arguments or because there was a 0 or 1 processed above, after
     * which we decremented the argument count (presumably from 2 to 1).
     */
    if ( argc > 1 )
    {
        printError("Usage:  %s [0|1]\n", argv[0]);
        return 0;
    }

    return 1;   /* Everything was OK! */
}

/*
 * testSearch tests the findLabel function, printing out the label being
 * searched for and either the address where it was found or, if it was
 * not found, an address of -1 and a message that the label was not in
 * the table.
 * @param  table        a pointer to the table through which to search
 * @param  searchLabel  the label to search for
 */
static void testSearch(LabelTable * table, char * searchLabel)
{
    printf("\n%s\e[3;36m%s\e[0m\n", "Looking for: ", searchLabel);

    int address;
    address = findLabel(table, searchLabel);

    if (address > -1) // this only works with addresses greater than -1! To use negative addresses, modify to (address != -1), and document appropriately.
        printf("\e[32m%s\e[0m\e[96m%s\e[0m%s\e[95m%d\e[0m\n", "\tFound ", searchLabel, " at address ", address);
    else if ( address == -1 )
        printf("\t \e[91m!>\e[0m The label you're looking for does not exist.\n");
}
