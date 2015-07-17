#include "UnitTest.h"
#include "../util.h"
#include "../shared_memory.h"


/**
 */
int test_exists() {
	int valid = 0;
	int result;

	result = shmExists("test_key");
	valid += assertTrue("test_exists: The key does not exists", result == SHM_ERROR_NOT_FOUND);

	result = shmStore("test_key", "abcde");
	valid += assertTrue("test_exists: shmStore should work", result == STATUS_SUCCESS);

	result = shmExists("test_key");
	valid += assertTrue("test_exists: The key does not exists", result == SHM_ERROR_FOUND);

	shmDelete("test_key");

	result = shmExists("test_key");
	valid += assertTrue("test_exists: The key does not exists", result == SHM_ERROR_NOT_FOUND);

	return valid;
}

int test_store() {
	int valid = 0;
	int result;

	result = shmStore("test_key", "abcde");
	valid += assertTrue("test_store: shmStore should work", result == STATUS_SUCCESS);

	result = shmStore("test_key2", "12345");
	valid += assertTrue("test_store: shmStore should work", result == STATUS_SUCCESS);

	result = shmStore("test_key", "abcde");
	valid += assertTrue("test_store: shmStore NOT should work", result == SHM_ERROR_OPEN);

	shmDelete("test_key");

	result = shmStore("test_key", "abcde");
	valid += assertTrue("test_store: shmStore should work", result == STATUS_SUCCESS);

	shmDelete("test_key");
	shmDelete("test_key2");

	return valid;
}

int test_fetch() {
	int valid = 0;
	int result;
	char * test1;

	result = shmStore("test_key", "abcde");
	valid += assertTrue("test_fetch: shmStore should work", result == STATUS_SUCCESS);

	result = shmFetch("test_key", &test1); 
	valid += assertTrue("test_fetch: shmFetch should work", result == STATUS_SUCCESS);

	result = strcmp("abcde", test1);
	valid += assertTrue("test_exists: The data should match", result == 0);

	shmDelete("test_key");

	return valid;
}

int test_delete() {
	int valid = 0;
	int result;
	char * test1;

	result = shmStore("test_key", "abcde");
	valid += assertTrue("test_delete: shmStore should work", result == STATUS_SUCCESS);

	shmDelete("test_key");

	result = shmFetch("test_key", &test1); 
	valid += assertTrue("test_delete: shmFetch should NOT work", result == SHM_ERROR_OPEN);

	result = shmExists("test_key");
	valid += assertTrue("test_delete: The key does not exists", result == SHM_ERROR_NOT_FOUND);

	return valid;
}

/* Define UnitTests Lookup functions */

int getNumberTest() {
	return 4;
}

void getUnitTest(UnitTestFunction tests[], char *list[])
{
	int id = 0;

	tests[id]	= test_exists;
	list[id++] = "test_exists";

	tests[id]	= test_store;
	list[id++] = "test_store";

	tests[id]	= test_fetch;
	list[id++] = "test_fetch";

	tests[id]	= test_delete;
	list[id++] = "test_delete";

}
