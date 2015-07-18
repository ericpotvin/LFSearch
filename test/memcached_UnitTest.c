#include "UnitTest.h"
#include "../util.h"
#include "../memcached.h"

/**
 */
int test_connect() {
	int valid = 0;

	memcached_st * mcc = mcConnect("localhost", 11211);
	valid += assertTrue("test_connect: localhost connection should work on 11211", mcc != NULL);

	memcached_st * mcc2 = mcConnect("a", 1);
	valid += assertTrue("test_connect: localhostinvalid connection should fail on 11211", mcc2 == NULL);

	return valid;
}

/**
 */
int test_exists() {
	int valid = 0;
	int result;

	memcached_st * mcc = mcConnect("localhost", 11211);
	valid += assertTrue("test_connect: localhost connection should work on 11211", mcc != NULL);

	result = mcExists(mcc, "exist_key");
	valid += assertTrue("test_exists: The key does not exists", result == MEMCACHED_NOTFOUND);

	result = mcStore(mcc, "exist_key", "abcde", 1, 0);
	valid += assertTrue("test_exists: mcStore should work 10 seconds", result == MEMCACHED_SUCCESS);

	result = mcExists(mcc, "exist_key");
	valid += assertTrue("test_exists: The key does exists", result == MEMCACHED_SUCCESS);

	mcDelete(mcc, "exist_key");

	result = mcExists(mcc, "exist_key");
	valid += assertTrue("test_exists: The key does not exists", result == MEMCACHED_NOTFOUND);

	return valid;
}

int test_store() {
	int valid = 0;
	int result;

	memcached_st * mcc = mcConnect("localhost", 11211);
	valid += assertTrue("test_store: localhost connection should work on 11211", mcc != NULL);

	result = mcStore(mcc, "store_key1", "abcde", 10, 0);
	valid += assertTrue("test_store: mcStore should work 10 seconds", result == MEMCACHED_SUCCESS);

	result = mcStore(mcc, "store_key2", "abcde", 10, 0);
	valid += assertTrue("test_store: mcStore should work 10 seconds", result == MEMCACHED_SUCCESS);

	mcDelete(mcc, "store_key1");
	mcDelete(mcc, "store_key2");

	result = mcExists(mcc, "store_key1");
	valid += assertTrue("test_store: The key1 does not exists", result == MEMCACHED_NOTFOUND);

	result = mcExists(mcc, "store_key2");
	valid += assertTrue("test_store: The key2 does not exists", result == MEMCACHED_NOTFOUND);

	mcFlush(mcc);

	return valid;
}

int test_fetch() {
	int valid = 0;
	int result;
	char * test1;

	memcached_st * mcc = mcConnect("localhost", 11211);
	valid += assertTrue("test_fetch: localhost connection should work on 11211", mcc != NULL);

	result = mcStore(mcc, "fetch_key", "abcde", 10, 0);
	valid += assertTrue("test_fetch: mcStore should work", result == STATUS_SUCCESS);

	result = mcFetch(mcc, "fetch_key", &test1); 
	valid += assertTrue("test_fetch: mcFetch should work", result == STATUS_SUCCESS);

	result = strcmp("abcde", test1);
	valid += assertTrue("test_exists: The data should match", result == 0);

	mcFlush(mcc);

	return valid;
}

int test_delete() {
	int valid = 0;
	int result;
	char * test1;

	memcached_st * mcc = mcConnect("localhost", 11211);
	valid += assertTrue("test_delete: localhost connection should work on 11211", mcc != NULL);

	result = mcStore(mcc, "del_key", "abcde", 10, 0);
	valid += assertTrue("test_delete: mcStore should work 10 seconds", result == MEMCACHED_SUCCESS);

	mcDelete(mcc, "del_key");

	result = mcExists(mcc, "del_key");
	valid += assertTrue("test_delete: The key does exists", result == MEMCACHED_NOTFOUND);

	mcFlush(mcc);

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
