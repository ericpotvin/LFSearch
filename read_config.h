struct config 
{
  char search_dir[CONFIG_BUFFER];
  char action[CONFIG_BUFFER];
  int limit;
  int read_buffer;
	char output[CONFIG_BUFFER];
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
 * validateConfig()
 * Validate the configuration file
 *
 * Input: (Struct config *) conf: The config structure
 * Return: unsigned Int
 */
unsigned int validateConfig(struct config * conf);
