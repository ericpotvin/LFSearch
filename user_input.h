/**
 * hasConfileFile()
 * Check if the list of params has the --config param
 *
 * Input: (Int) c: Argument counts
 * Input: (Char*) a: Arguments list
 * Return: Integer
 */
unsigned int hasConfileFile(int c, char * a[]);

/**
 * validateInputs()
 * Validate the inputs
 *
 * Input: (Char*) param: The param name
 * Input: (Char*) value: The param value
 * Return: Integer
 */
unsigned int validateInputs(char * param, char * value);
