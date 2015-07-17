/**
 * scanFile()
 * Look for a string in a file
 *
 * Input: (Char*) filename: The Filename
 * Input: (Char*) content: The search string
 * Return: Integer
 */
unsigned int scanFile(char * filename, char * searchString);

/**
 * scanDir()
 * Look for a string in a folder recursively
 *
 * Input: (Char*) filename: The Filename
 * Input: (Char*) content: The search string
 * Return: Integer
 */
unsigned int scanDir(char * root, char * searchString);
