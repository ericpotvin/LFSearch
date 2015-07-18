#include <libmemcached/memcached.h>

/**
 * mcConnect()
 * Connect to a memecache server
 *
 * Input: (Char*) server: The memcache server
 * Input: (Int) port: The memcache server port
 * Return: memcached_st pointer
 */
memcached_st * mcConnect(char * server, int port);

/**
 * mcExists()
 * Check if a memcached exists for a key
 *
 * Input: (memcached_st*) mc: The memcached connection
 * Input: (Char*) key: The unique key
 * Return: Integer
 */
unsigned int mcExists(memcached_st *mc, char * key);

/**
 * mcStore()
 * Store to memcached
 *
 * Input: (memcached_st*) mc: The memcached connection
 * Input: (Char*) key: The unique key
 * Input: (Char*) data: The data to be stored
 * Input: (time_t) expire: How long we retain the data (in seconds)
 * Input: (uint32_t) flags: The behavior flags
 * Return: Integer
 */
unsigned int mcStore(memcached_st *mc,
										 char * key,
										 char * data,
										 time_t expire,
										 uint32_t flags);

/**
 * mcFetch()
 * Fetch to memcached
 *
 * Input: (memcached_st*) mc: The memcached connection
 * Input: (Char*) key: The unique key
 * Input: (Char*) data: The data to be fetched into
 * Return: Integer
 */
unsigned int mcFetch(memcached_st *mc, char * key, char ** data);

/**
 * mcDelete()
 * Delete a key in the memcached
 *
 * Input: (memcached_st*) mc: The memcached connection
 * Input: (Char*) key: The unique key
 * Return: Integer
 */
unsigned int mcDelete(memcached_st *mc, char * key);

/**
 * mcFlush()
 * Flush all memcache keys
 *
 * Input: (memcached_st*) mc: The memcached connection
 */
unsigned int mcFlush(memcached_st *mc);
