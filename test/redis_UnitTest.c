#include "UnitTest.h"
#include "../util.h"
#include "../redis.h"

/**
 */
int test_connect() {
	int valid = 0;

	redisContext * rc = rdsConnect("localhost", 6379);
	valid += assertTrue("test_connect: localhost connection should work on 6379", rc != NULL);

	redisContext * rc2 = rdsConnect("a", 1);
	valid += assertTrue("test_connect: invalid connection should fail on server a, port 1", rc2 == NULL);

	return valid;
}

/**
 */
int test_exists() {
	int valid = 0;
	int result;

	redisContext * rc = rdsConnect("localhost", 6379);
	valid += assertTrue("test_connect: localhost connection should work on 6379", rc != NULL);

	result = rdsExists(rc, "exist_key");
	valid += assertTrue("test_exists: The key does not exists", result == STATUS_FAILURE);

	result = rdsStore(rc, "exist_key", "abcde", 10);
	valid += assertTrue("test_exists: redisStore should work 10 seconds", result == STATUS_SUCCESS);

	result = rdsExists(rc, "exist_key");
	valid += assertTrue("test_exists: The key does exists", result == STATUS_SUCCESS);

	rdsDelete(rc, "exist_key");

	result = rdsExists(rc, "exist_key");
	valid += assertTrue("test_exists: The key does not exists", result == STATUS_FAILURE);

	return valid;
}

int test_store() {
	int valid = 0;
	int result;

	redisContext * rc = rdsConnect("localhost", 6379);
	valid += assertTrue("test_store: localhost connection should work on 6379", rc != NULL);

	result = rdsStore(rc, "store_key1", "abcde", 10);
	valid += assertTrue("test_store: redisStore should work 10 seconds", result == STATUS_SUCCESS);

	result = rdsStore(rc, "store_key2", "abcde", 10);
	valid += assertTrue("test_store: redisStore should work 10 seconds", result == STATUS_SUCCESS);

	rdsDelete(rc, "store_key1");
	rdsDelete(rc, "store_key2");

	result = rdsExists(rc, "store_key1");
	valid += assertTrue("test_store: The key1 does not exists", result == STATUS_FAILURE);

	result = rdsExists(rc, "store_key2");
	valid += assertTrue("test_store: The key2 does not exists", result == STATUS_FAILURE);

	rdsFlush(rc);

	return valid;
}

int test_fetch() {
	int valid = 0;
	int result;
	char * test1;
	char * test2;

	redisContext * rc = rdsConnect("localhost", 6379);
	valid += assertTrue("test_fetch: localhost connection should work on 6379", rc != NULL);

	result = rdsStore(rc, "fetch_key", "abcde", 10);
	valid += assertTrue("test_fetch: redisStore should work", result == STATUS_SUCCESS);

	result = rdsFetch(rc, "fetch_key", &test1); 
	valid += assertTrue("test_fetch: redisFetch should work", result == STATUS_SUCCESS);

	result = rdsFetch(rc, "fetch_key_not_found", &test2); 
	valid += assertTrue("test_fetch: redisFetch should work", result == STATUS_FAILURE);

	result = strcmp("abcde", test1);
	valid += assertTrue("test_exists: The data should match", result == 0);

	rdsFlush(rc);

	return valid;
}

int test_delete() {
	int valid = 0;
	int result;
	char * test1;

	redisContext * rc = rdsConnect("localhost", 6379);
	valid += assertTrue("test_delete: localhost connection should work on 6379", rc != NULL);

	result = rdsStore(rc, "del_key", "abcde", 10);
	valid += assertTrue("test_delete: redisStore should work 10 seconds", result == STATUS_SUCCESS);

	rdsDelete(rc, "del_key");

	result = rdsExists(rc, "del_key");
	valid += assertTrue("test_delete: The key does exists", result == STATUS_FAILURE);

	rdsFlush(rc);

	return valid;
}

/* Define UnitTests Lookup functions */

int getNumberTest() {
	return 5;
}

void getUnitTest(UnitTestFunction tests[], char *list[]) {
	int id = 0;

	tests[id]	= test_connect;
	list[id++] = "test_connect";

	tests[id]	= test_exists;
	list[id++] = "test_exists";

	tests[id]	= test_store;
	list[id++] = "test_store";

	tests[id]	= test_fetch;
	list[id++] = "test_fetch";

	tests[id]	= test_delete;
	list[id++] = "test_delete";

}
