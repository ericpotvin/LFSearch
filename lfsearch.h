#include "util.h"
#include "infile_search.h"
#include "shared_memory.h"

/**
 * validateInput()
 * Validate the input parameters
 *
 * argv[0] = program
 * argv[1] = action (scan, get, store, delete, exists)
 * argv[2] = data to search
 * argv[3] = /path/to/filename
 *
 * Input: (Int) argc: The number of argument
 * Input: (Char*) argv[]: The arguments
 */
unsigned int validateInput(int argc, char *argv[]);

/**
 * validateAction()
 * Get the action
 *
 * Input: (Char*) val: The argument from the command line
 * Input: (Int*) action: The action
 * Return Int
 */
unsigned int validateAction(char *val, int * action);

/**
 * getFileType()
 * Get the file type
 *
 * Input: (Char*) file: The filename
 * Return Int
 */
unsigned int getFileType(char * file, int * type);
