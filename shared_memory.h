/**
 * shmExists()
 * Check if a shared memory exists for a key
 *
 * Input: (Char*) key: The unique key
 * Return: Integer
 */
unsigned int shmExists(char * key);

/**
 * shmStore()
 * Store to shared memory
 *
 * Input: (Char*) key: The unique key
 * Input: (Char*) data: The data to be stored
 * Return: Integer
 */
unsigned int shmStore(char * key, char * data);

/**
 * shmFetch()
 * Fetch to shared memory
 *
 * Input: (Char*) key: The unique key
 * Input: (Char*) data: The data to be fetched into
 * Return: Integer
 */
unsigned int shmFetch(char * key, char ** data);

/**
 * shmDelete()
 * Delete a key in the shared memory
 *
 * Input: (Char*) key: The unique key
 * Return: Integer
 */
unsigned int shmDelete(char * key);
