#include "UnitTest.h"
#include "../util.h"

#define BLANK_FILENAME "/tmp/blank_file"

/**
 * Create the config filename
 */
void createBlankFile(char * filename) {
	FILE *fp;
	fp = fopen(filename, "w+");
	fputs("", fp);
	fclose(fp);
}

/**
 */
int test_hasConfileFile() {
	int valid = 0;
	int result;

	int argc1 = 3;
	char * argv1[3] = { "", "--config", "/tmp/badfile" };

	result = hasConfileFile(argc1, argv1);
	valid += assertTrue("test_hasConfileFile: The config file does not exists", result == USER_INPUT_NO_CONFIG_FOUND);

	//

	int argc2 = 5;
	char * argv2[5] = { "", "--search", "abc", "--config", "/tmp/badfile" };

	result = hasConfileFile(argc2, argv2);
	valid += assertTrue("test_hasConfileFile: The config file does not exists", result == USER_INPUT_NO_CONFIG_FOUND);

	//

	int argc3 = 5;
	char * argv3[5] = { "", "--search", "abc", "--config", BLANK_FILENAME };

	createBlankFile(BLANK_FILENAME);

	result = hasConfileFile(argc3, &argv3);
	valid += assertTrue("test_hasConfileFile: The config file does exists", result == STATUS_SUCCESS);

	remove(BLANK_FILENAME);

	return valid;
}

/**
 */
int test_validateInputs() {
	int valid = 0;
	int result;

	result = validateInputs("action", "scan");
	valid += assertTrue("test_validateInputs: action is not valid", result == STATUS_FAILURE);

	// action

	result = validateInputs("--action", "scan");
	valid += assertTrue("test_validateInputs: Scan is a valid action", result == STATUS_SUCCESS);

	result = validateInputs("--action", "exists");
	valid += assertTrue("test_validateInputs: Scan is a valid action", result == STATUS_SUCCESS);

	result = validateInputs("--action", "fetch");
	valid += assertTrue("test_validateInputs: Scan is a valid action", result == STATUS_SUCCESS);

	result = validateInputs("--action", "store");
	valid += assertTrue("test_validateInputs: Scan is a valid action", result == STATUS_SUCCESS);

	result = validateInputs("--action", "delete");
	valid += assertTrue("test_validateInputs: Scan is a valid action", result == STATUS_SUCCESS);

	result = validateInputs("--action", "invalid");
	valid += assertTrue("test_validateInputs: invalid is not a valid action", result == CONFIG_ERROR_ACTION);

	// engine

	result = validateInputs("--engine", "mc");
	valid += assertTrue("test_validateInputs: mc is a valid engine", result == STATUS_SUCCESS);

	result = validateInputs("--engine", "shm");
	valid += assertTrue("test_validateInputs: shm is a valid engine", result == STATUS_SUCCESS);

	result = validateInputs("--engine", "invalid");
	valid += assertTrue("test_validateInputs: invalid is not a valid engine", result == CONFIG_ERROR_ENGINE);

	// search

	result = validateInputs("--search", "test");
	valid += assertTrue("test_validateInputs: test is a valid search", result == STATUS_SUCCESS);

	result = validateInputs("--search", "");
	valid += assertTrue("test_validateInputs: (empty) is not a valid engine", result == CONFIG_ERROR_SEARCH);

	// file

	result = validateInputs("--file", BLANK_FILENAME);
	valid += assertTrue("test_validateInputs: BLANK_FILENAME is a valid file", result == CONFIG_ERROR_FILE);

	createBlankFile(BLANK_FILENAME);
	result = validateInputs("--file", BLANK_FILENAME);
	valid += assertTrue("test_validateInputs: BLANK_FILENAME is a valid file", result == STATUS_SUCCESS);
	remove(BLANK_FILENAME);

	result = validateInputs("--file", "/tmp/");
	valid += assertTrue("test_validateInputs: /tmp/ is a valid dir", result == STATUS_SUCCESS);

	result = validateInputs("--file", "/tmp/3q084gh0w3q840hg8");
	valid += assertTrue("test_validateInputs: /tmp/ is a valid dir", result == CONFIG_ERROR_FILE);

	// limit

	result = validateInputs("--limit", 0);
	valid += assertTrue("test_validateInputs: 0 is not a valid limit", result == CONFIG_ERROR_LIMIT);

	result = validateInputs("--limit", 1);
	valid += assertTrue("test_validateInputs: 1 is a valid limit", result == STATUS_SUCCESS);

	result = validateInputs("--limit", 100);
	valid += assertTrue("test_validateInputs: 100 is a valid limit", result == STATUS_SUCCESS);

	result = validateInputs("--limit", -100);
	valid += assertTrue("test_validateInputs: -100 is a valid limit", result == CONFIG_ERROR_LIMIT);

	result = validateInputs("--limit", 1024);
	valid += assertTrue("test_validateInputs: 1024 is a valid limit", result == STATUS_SUCCESS);

	result = validateInputs("--limit", 1025);
	valid += assertTrue("test_validateInputs: 1025 is not a valid limit", result == CONFIG_ERROR_LIMIT);

	// read buffer

	result = validateInputs("--read_buffer", 0);
	valid += assertTrue("test_validateInputs: 0 is not a valid read_buffer", result == CONFIG_ERROR_READ_BUFFER);

	result = validateInputs("--read_buffer", 1);
	valid += assertTrue("test_validateInputs: 1 is a valid read_buffer", result == STATUS_SUCCESS);

	result = validateInputs("--read_buffer", 100);
	valid += assertTrue("test_validateInputs: 100 is a valid read_buffer", result == STATUS_SUCCESS);

	result = validateInputs("--read_buffer", -100);
	valid += assertTrue("test_validateInputs: -100 is a valid read_buffer", result == CONFIG_ERROR_READ_BUFFER);

	result = validateInputs("--read_buffer", 255);
	valid += assertTrue("test_validateInputs: 255 is a valid read_buffer", result == STATUS_SUCCESS);

	result = validateInputs("--read_buffer", 256);
	valid += assertTrue("test_validateInputs: 256 is not a valid read_buffer", result == CONFIG_ERROR_READ_BUFFER);

	// output

	result = validateInputs("--output", "screen");
	valid += assertTrue("test_validateInputs: screen is a valid ouput", result == STATUS_SUCCESS);

	result = validateInputs("--output", "/abc/def/zyw");
	valid += assertTrue("test_validateInputs: /abc/def/zyw is not a valid ouput (ENOENT)", result == ENOENT);

	createBlankFile(BLANK_FILENAME);
	result = validateInputs("--output", BLANK_FILENAME);
	valid += assertTrue("test_validateInputs: BLANK_FILENAME is not a valid ouput (CONFIG_ERROR_OUTPUT_FILE_EXISTS)", result == CONFIG_ERROR_OUTPUT_FILE_EXISTS);
	remove(BLANK_FILENAME);

	result = validateInputs("--output", "/etc/");
	valid += assertTrue("test_validateInputs: /etc/ is not a valid ouput (EACCES)", result == EACCES);

	return valid;
}

/* Define UnitTests Lookup functions */

int getNumberTest() {
	return 2;
}

void getUnitTest(UnitTestFunction tests[], char *list[])
{
	int id = 0;

	tests[id]	= test_hasConfileFile;
	list[id++] = "test_hasConfileFile";

	tests[id]	= test_validateInputs;
	list[id++] = "test_validateInputs";
}
