struct config 
{
  char search_dir[CONFIG_BUFFER];
  char action[CONFIG_BUFFER];
  int limit;
  int read_buffer;
} config;

/**
 * getConfig()
 * Get the configuration of a file
 *
 * Input: (Char*) filename: The Filename
 * Input: (Struct config *) conf: The config structure
 * Return: Int
 */
int getConfig(char * filename, struct config * conf);
