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
 * getDirList()
 * Get the files in a directory
 *
 * Input: (Char*) root: The root directory
 * Input: (Char*) list[]: The list
 * Input: (Int*) count: The number of element found
 */
void getDirList(char * root, char * list[], int * count);
