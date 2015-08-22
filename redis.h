#include <hiredis.h>

/**
 * rdsConnect()
 * Connect to a redis server
 *
 * Input: (Char*) server: The redis server
 * Input: (Int) port: The redis server port
 * Return: redisContext pointer
 */
redisContext * rdsConnect(char * server, int port);

/**
 * rdsExists()
 * Check if a redis exists for a key
 *
 * Input: (redisContext*) redis: The redis connection
 * Input: (Char*) key: The unique key
 * Return: Integer
 */
unsigned int rdsExists(redisContext *rc, char * key);

/**
 * rdsStore()
 * Store to redis
 *
 * Input: (redisContext*) redis: The redis connection
 * Input: (Char*) key: The unique key
 * Input: (Char*) data: The data to be stored
 * Input: (uInt) expire: How long we retain the data (in seconds)
 * Return: Integer
 */
unsigned int rdsStore(redisContext *rc,
										 char * key,
										 char * data,
										 unsigned int expire);

/**
 * rdsFetch()
 * Fetch to redis
 *
 * Input: (redisContext*) redis: The redis connection
 * Input: (Char*) key: The unique key
 * Input: (Char*) data: The data to be fetched into
 * Return: Integer
 */
unsigned int rdsFetch(redisContext *rc, char * key, char ** data);

/**
 * rdsDelete()
 * Delete a key in the redis
 *
 * Input: (redisContext*) redis: The redis connection
 * Input: (Char*) key: The unique key
 * Return: Integer
 */
unsigned int rdsDelete(redisContext *rc, char * key);

/**
 * rdsDisconnect()
 * Disconnect a redis server
 *
 * Input: (redisContext*) redis: The redis connection
 */
void rdsDisconnect(redisContext *rc);

/**
 * rdsFlush()
 * Flush all redis keys
 *
 * Input: (redisContext*) redis: The redis connection
 */
void rdsFlush(redisContext *rc);
