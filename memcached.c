#include "util.h"
#include "memcached.h"
#include <math.h>

/**
 */
memcached_st * mcConnect(char * server, int port) {

	char mcServer[256];
	memcached_st *memc = NULL;

	snprintf(mcServer, sizeof mcServer, "--SERVER=%s:%d", server, port);

	memc = memcached(mcServer, strlen(mcServer));

	if(memc == NULL) {
		if(DEBUG) {
			printf("DEBUG: Cannot connect to %s:%d\n", server, port);
		}
	}

	return memc;
}

/**
 */
unsigned int mcExists(memcached_st *mc, char * key) {

  memcached_return rc;
	int len = strlen(key);

	if(mc == NULL) {
		return MEMCACHED_CONNECTION_FAILURE;
	}

	rc = memcached_exist(mc, key, len);

	if(rc == MEMCACHED_NOTFOUND) {
		if(DEBUG) {
			printf("DEBUG: Key '%s' not found\n", key);
		}
		return MEMCACHED_NOTFOUND;
	}

	if(DEBUG) {
		printf("DEBUG: Key '%s' found\n", key);
	}

	return MEMCACHED_SUCCESS;	
}

/**
 */
unsigned int mcStore(memcached_st *mc,
										 char * key,
										 char * data,
										 time_t expire,
										 uint32_t flags) {

  memcached_return rc;
	int lenKey = strlen(key);
	int lenData = strlen(data);

	if(mc == NULL) {
		return MEMCACHED_CONNECTION_FAILURE;
	}

  rc = memcached_set(mc, key, lenKey, data, lenData, expire, flags);

  if (rc == MEMCACHED_SUCCESS) {
		if(DEBUG) {
			printf("DEBUG: Key (%s) stored successfully\n", key);
		}
		return MEMCACHED_SUCCESS;
	}

	if(DEBUG) {
		printf("DEBUG: Couldn't store key: '%s'. Error: %s\n", key, memcached_strerror(mc, rc));
	}

	return MEMCACHED_FAILURE;
}

/**
 */
unsigned int mcFetch(memcached_st *mc, char * key, char ** data) {

	size_t vlen;
	uint32_t flags;
	memcached_return mrc;

	if(mc == NULL) {
		return MEMCACHED_CONNECTION_FAILURE;
	}

	(*data) = memcached_get(mc, key, strlen(key), &vlen, &flags, &mrc);

  if (mrc == MEMCACHED_SUCCESS) {
		if(DEBUG) {
			printf("DEBUG: Key (%s) fetched successfully\n", key);
		}
		return MEMCACHED_SUCCESS;
	}
	
	if(DEBUG) {
		printf("DEBUG: Couldn't fetch key: '%s'. Error: %s\n", key, memcached_strerror(mc, mrc));
	}

	return MEMCACHED_FAILURE;
}

/**
 */
unsigned int mcDelete(memcached_st *mc, char * key) {

  memcached_return rc;
	int len = strlen(key);

	if(mc == NULL) {
		return MEMCACHED_CONNECTION_FAILURE;
	}

	rc = memcached_delete(mc, key, len, 0);

  if (rc == MEMCACHED_SUCCESS) {
		if(DEBUG) {
			printf("DEBUG: Key (%s) deleted successfully\n", key);
		}
		return MEMCACHED_SUCCESS;
	}
	
	if(DEBUG) {
		printf("DEBUG: Couldn't delete key: '%s'. Error: %s\n", key, memcached_strerror(mc, rc));
	}

	return MEMCACHED_FAILURE;
}

/**
 */
unsigned int mcFlush(memcached_st *mc) {
	if(mc == NULL) {
		return MEMCACHED_CONNECTION_FAILURE;
	}

	memcached_free(mc);
	return MEMCACHED_SUCCESS;
}
