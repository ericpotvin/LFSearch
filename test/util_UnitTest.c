#include "UnitTest.h"
#include "../util.h"

/**
 */
int test_trim() {
	int valid = 0;
	int result;

	char str1[] = "abcdef";
	char str2[] = " abcdef";

	result = strcmp(str1, trim(str2));
	valid += assertTrue("test_trim: Should be equal", result == 0);

	char str3[] = "abcdef";
	char str4[] = "abcdef	";

	result = strcmp(str3, trim(str4));
	valid += assertTrue("test_trim: Should be equal", result == 0);

	char str5[] = "abcdef";
	char str6[] = "					 abcdef						";

	result = strcmp(str5, trim(str6));
	valid += assertTrue("test_trim: Should be equal", result == 0);

	return valid;
}

/**
 */
int test_isFile() {
	int valid = 0;
	int result;

	result = isFile("/etc/hosts");
	valid += assertTrue("test_isFile: /etc/hosts is a file", result == 1);

	result = isFile("/etc");
	valid += assertTrue("test_isFile: /etc is a folder", result == 0);

	return valid;
}

/**
 */
int test_isDir() {
	int valid = 0;
	int result;

	result = isDir("/etc/hosts");
	valid += assertTrue("test_isDir: /etc/hosts is a file", result == 0);

	result = isDir("/etc");
	valid += assertTrue("test_isDir: /etc is a folder", result == 1);

	return valid;
}

/**
 */
int test_getMD5() {
	int valid = 0;
	int result;

	char * str1 = "Hello World";
	char * hash1;

	hash1 = getMD5(str1);
	result = strcmp("b10a8db164e0754105b7a99be72e3fe5", hash1);
	valid += assertTrue("test_getMD5: Hello World should be: b10a8db164e0754105b7a99be72e3fe5", result == 0);

	free(hash1);

	char * str2 = "test";
	char * hash2;

	hash2 = getMD5(str2);
	result = strcmp("098f6bcd4621d373cade4e832627b4f6", hash2);
	valid += assertTrue("test_getMD5: test should be: 098f6bcd4621d373cade4e832627b4f6", result == 0);

	free(hash2);

	return valid;
}

/* Define UnitTests Lookup functions */

int getNumberTest() {
	return 4;
}

void getUnitTest(UnitTestFunction tests[], char *list[])
{
	int id = 0;

	tests[id]	= test_trim;
	list[id++] = "test_trim";

	tests[id]	= test_isFile;
	list[id++] = "test_isFile";

	tests[id]	= test_isDir;
	list[id++] = "test_isDir";

	tests[id]	= test_getMD5;
	list[id++] = "test_getMD5";
}
