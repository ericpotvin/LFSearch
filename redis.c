#include "util.h"
#include "redis.h"

/**
 */
redisContext * rdsConnect(char * server, int port) {

	redisContext *c;
	struct timeval timeout = { 1, 500000 }; // 1.5 seconds
	c = redisConnectWithTimeout(server, port, timeout);

	if(c == NULL) {
		printf("DEBUG: Unable to connect to redis (%s:%d).\n", server, port);
		return NULL;	
	}

	if(c->err) {
		if(DEBUG) {
			printf("DEBUG: Unable to connect to redis (%s:%d). Got error: %d\n", server, port, c->err);
		}
		redisFree(c);
		return NULL;
	}

	return c;
}

/**
 */
unsigned int rdsExists(redisContext *rc, char * key) {

	unsigned int ret;
	redisReply *reply;

	if(rc == NULL) {
		return REDIS_CONNECTION_FAIL;
	}

	reply = redisCommand(rc, "EXISTS %s", key);
	ret = reply->integer == 1 ? STATUS_SUCCESS : STATUS_FAILURE;
	freeReplyObject(reply);
	return ret;
}

/**
 */
unsigned int rdsStore(redisContext *rc,
										 char * key,
										 char * data,
										 unsigned int expire) {

	unsigned int ret;
	redisReply *reply;

	if(rc == NULL) {
		return REDIS_CONNECTION_FAIL;
	}

	if(expire == 0) {
		// SET mykey "myval"
		reply = redisCommand(rc, "SET %s %s", key, data);
	}
	else {
		// SETEX mykey 10 "myval"
		reply = redisCommand(rc, "SETEX %s %d %s", key, expire, data);
	}

	ret = strcasecmp(reply->str, "OK") == 0 ? STATUS_SUCCESS : STATUS_FAILURE;
	freeReplyObject(reply);

	return ret;
}

/**
 */
unsigned int rdsFetch(redisContext *rc, char * key, char ** data) {

	redisReply *reply;

	if(rc == NULL) {
		return REDIS_CONNECTION_FAIL;
	}

	reply = redisCommand(rc, "GET %s", key);

	if(reply->str == NULL || strcmp(reply->str,"") == 0) {
		return STATUS_FAILURE;
	}

	(*data) = strdup(reply->str);
	freeReplyObject(reply);

	return STATUS_SUCCESS;
}

/**
 */
unsigned int rdsDelete(redisContext *rc, char * key) {

	unsigned int ret;
	redisReply *reply;

	if(rc == NULL) {
		return REDIS_CONNECTION_FAIL;
	}

	reply = redisCommand(rc, "DEL %s", key);
	ret = reply->integer == 1 ? STATUS_SUCCESS : STATUS_FAILURE;
	freeReplyObject(reply);
	return ret;
}

/**
 */
void rdsDisconnect(redisContext *rc) {

	if(rc == NULL) {
		return;
	}

	redisFree(rc);
}

/**
 */
/**
 */
void rdsFlush(redisContext *rc) {

	unsigned int ret;
	redisReply *reply;

	if(rc == NULL) {
		return;
	}

	reply = redisCommand(rc, "FLUSHALL");
	freeReplyObject(reply);
}
