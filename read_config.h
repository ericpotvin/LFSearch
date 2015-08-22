struct config 
{
  char action[CONFIG_DEFAULT_BUFFER];
	char engine[CONFIG_DEFAULT_BUFFER];
  char search[CONFIG_DEFAULT_BUFFER];
	char file[CONFIG_DEFAULT_BUFFER];
  int limit;
  int read_buffer;
	char output[CONFIG_DEFAULT_BUFFER];
} config;

/**
 * getConfig()
 * Get the configuration of a file
 *
 * Input: (Char*) filename: The Filename
 * Input: (Struct config *) conf: The config structure
 * Return: unsigned Int
 */
unsigned int getConfig(char * filename, struct config * conf);

/**
 * knownParam()
 * Check if a param is known
 *
 * Input: (Char*) param: The parameter
 * Return: unsigned Int
 */
unsigned int knownParam(char * param);

/**
 * validateConfig()
 * Validate the configuration file
 *
 * Input: (Struct config *) conf: The config structure
 * Return: unsigned Int
 */
unsigned int validateConfig(struct config * conf);

/**
 * validateActionInput()
 * Validate the action 
 *
 * Input: (char*) value: The value
 * Return: unsigned Int
 */
unsigned int validateActionInput(char * value);

/**
 * validateEngineInput()
 * Validate the engine 
 *
 * Input: (char*) value: The value
 * Return: unsigned Int
 */
unsigned int validateEngineInput(char * value);

/**
 * validateSearchInput()
 * Validate the search 
 *
 * Input: (char*) value: The value
 * Return: unsigned Int
 */
unsigned int validateSearchInput(char * value);

/**
 * validateFileInput()
 * Validate the file (path or file)
 *
 * Input: (char*) value: The value
 * Return: unsigned Int
 */
unsigned int validateFileInput(char * value);

/**
 * validateLimitInput()
 * Validate the limit
 *
 * Input: (char*) value: The value
 * Return: unsigned Int
 */
unsigned int validateLimitInput(int value);

/**
 * validateReadBufferInput()
 * Validate the read buffer
 *
 * Input: (char*) value: The value
 * Return: unsigned Int
 */
unsigned int validateReadBufferInput(int value);

/**
 * validateOutputInput()
 * Validate the output 
 *
 * Input: (char*) value: The value
 * Return: unsigned Int
 */
unsigned int validateOutputInput(char * value);
