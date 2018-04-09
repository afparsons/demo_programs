/*
 * Label Table: functions to access and manipulate a label table
 *
 * This file provides the definitions of a set of functions for
 * creating, maintaining, and using a table of assembly language
 * instruction labels and the memory addresses associated with them.
 *
 * Author: Alyce Brady
 *
 * Creation Date:   2/16/99
 *   Modified:  12/20/2000   Updated postcondition information.
 *   Modified:  04/19/2013   Modernized call to fprintf for errors.
 *   Modified:  05/25/2015   Updated to use printError function.
 *   Modified:  04/06/2017   Completed PP1b (Andrew Parsons).
 *   Modified:  04/10/2017   Temp. fix for free() core dump (Andrew Parsons).   
 *
 *   Assistance from Danny Michelin in spotting a dumb mistake in testSearch().
 *   Assistance from Alyce Brady in troubleshooting the free() core dump error.
 *   Suggestion from Josh Gibson in resolving the free() core dump error.
*/

#include "assembler.h"

// internal global variables (global to this file only)
static const char * ERROR0 = "Error: no label table exists.\n";
static const char * ERROR1 = "Error: a duplicate label was found.\n";
static const char * ERROR2 = "Error: cannot allocate space in memory.\n";

// internal function (visible to this file only)
static int verifyTableExists(LabelTable * table);

void tableInit (LabelTable * table)
/* Postcondition: table is initialized to indicate that there are no label entries in it. */
{
    /* verify that current table exists */
    if ( ! verifyTableExists (table) ) 
    {
        printError("FATAL ERROR: table doesn't exist.");
        return; /* fatal error: table doesn't exist */
    }

    /* initialize the properties of the LabelTable struct */
    (*table).nbrLabels = 0;
    (*table).capacity = 0;
    (*table).entries = NULL;
}

void printLabels (LabelTable * table)
/* Postcondition: all the labels in the table, with their associated addresses, have been printed to the standard output. */
{
    int i;

    /* if the table doesn't exist, tell the user */
    if ( table == NULL )
        (void) printf ("\nLabel Table is a NULL pointer.\n");
    
    /* if the table does exist, print the number of labels and its contents */
    else 
    {
        (void) printf ("\nThere are %d labels in the table:\n", (*table).nbrLabels);
        
        printf("%-16s%-16s\n", "--\e[4mLabel\e[0m---------", "-------\e[4mAddress\e[0m------");
        printf("%s\n", "------------------------------------");

        for (i = 0; i < (*table).nbrLabels; i++) 
        {
                printf("%s%-16s%-5s%-16d\n","  ",(*table).entries[i].label, " @   ", (*table).entries[i].address);
        }
    }
}

/* Returns the address associated with the label; -1 if label is not in the table or table doesn't exist. */
int findLabel (LabelTable * table, char * label) 
{
    /* iterate through the LabelTable, using strcmp() to compare the ith string with the sought label */
    int i;
    for (i = 0; i < (*table).nbrLabels; i++)
    {
        if (strcmp( (*table).entries[i].label, label) == 0) 
        {
            return (*table).entries[i].address;
        }
    }

    return -1;
}

int addLabel (LabelTable * table, char * label, int address)
/* Postcondition: if label was already in table, the table is unchanged; otherwise a new entry has been added to the 
 * table with the specified label name and instruction address (memory location) and the table has been resized if necessary.
 * Returns 1 if no fatal errors occurred; 0 if memory allocation error or table doesn't exist.
 */
{
    char * labelDuplicate;

    /* verify that current table exists */
    if ( ! verifyTableExists (table) ) 
    {
        printError("fatal error: table doesn't exist\n");
        return 0;           /* fatal error: table doesn't exist */
    }
    
    /* Is the label already in the table? */
    if ( findLabel(table, label) != -1)
    {
        printError("%s\n", ERROR1);
        return 0;
    }

    /* Create a dynamically allocated version of label that will persist. */
    /*   NOTE: on some machines you may need to make this _strdup !  */
    if ((labelDuplicate = strdup (label)) == NULL) 
    {
        printError ("%s", ERROR2);
        return 0;           /* fatal error: couldn't allocate memory */
    }

    /* Resize the table if necessary. */
    if ( (*table).nbrLabels >= (*table).capacity ) 
    {  
        /* Per Alyce's suggestion, I've adapted the Java ArrayList growth rate of 1.5 to tableResize */
        tableResize(table, ((*table).capacity * 3) / 2 + 1);
    }

    /* Add the label */
        // this is a little confusing... go to the first address of the table
        // then add the total number of entries, and that is the first open space.
        // example: [0] + 3 = 3... [3] is the first open space ([0..2] are taken).
    LabelEntry * entry = (*table).entries + (*table).nbrLabels;
    (*entry).label = labelDuplicate;
    (*entry).address = address;
    (*table).nbrLabels += 1;
    
    return 1;               /* everything worked */
}

/* Warning: Thar be dragons ahead! */
int tableResize (LabelTable * table, int newSize)
  /* Postcondition: table now has the capacity to hold newSize label entries. If the new size is smaller than the old size, 
   * the table is truncated after the first newSize entries.
   * Returns 1 if everything went OK; 0 if memory allocation error or table doesn't exist.
   */
{
    char *       ptr;               /* points to any byte in memory */
    LabelEntry * newEntryList;
    int          smaller;

    /* verify that current table exists */
    if ( ! verifyTableExists (table) )
        return 0;           /* fatal error: table doesn't exist */

    /* create a new internal table of the specified size */
    if ((newEntryList = malloc (newSize * sizeof(LabelEntry))) == NULL)
    {
        printError ("%s", ERROR2);
        return 0;           /* fatal error: couldn't allocate memory */
    }

    if ( (*table).entries )           /* if there were entries */
    {
        /* move contents of internal table to new internal table */
        smaller = (*table).nbrLabels < newSize ? (*table).nbrLabels : newSize;
        (void) memcpy (newEntryList, (*table).entries, smaller * sizeof(LabelEntry));

        /* free the space taken up by the old internal table */
        free ((*table).entries);
        (*table).nbrLabels = smaller;
    }

    (*table).entries = newEntryList;
    (*table).capacity = newSize;
    return 1;
}

static int verifyTableExists(LabelTable * table)
/* Returns true (1) if table exists; prints an error and returns false (0) otherwise. */
{
    /* verify that current table exists */
    if ( ! table )
    {
        printError ("%s", ERROR0);
        return 0;
    }
    return 1;
}