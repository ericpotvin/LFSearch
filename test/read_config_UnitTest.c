#include "UnitTest.h"
#include "../util.h"
#include "../read_config.h"

#define CONFIG_FILENAME "/tmp/test1.conf"

#define CONFIG_GOOD_1 "file=/tmp/\nengine=mc\nsearch=str\naction=scan\nlimit=1\nread_buffer=10\noutput=screen"
#define CONFIG_GOOD_2 "file=/tmp/\nengine=shm\nsearch=zzz\naction=fetch\nlimit=12\nread_buffer=100\noutput=/tmp/file.txt"

#define CONFIG_BAD_ACTION "file=/tmp/\nengine=mc\naction=list\nlimit=12\nread_buffer=100\noutput=screen"
#define CONFIG_BAD_ENGINE "file=/tmp/\nengine=none\naction=fetch\nlimit=1\nread_buffer=100\noutput=/tmp/fxml"
#define CONFIG_BAD_SEARCH "search=\nfile=/tmp/\nengine=mc\naction=scan\nlimit=12\nread_buffer=100\noutput=screen"
#define CONFIG_BAD_FILE   "file=/zzz/\nengine=mc\naction=fetch\nlimit=1\nread_buffer=100\noutput=screen\nsearch=abc"
#define CONFIG_BAD_LIMIT  "file=/tmp/\nengine=mc\naction=fetch\nlimit=-1\nread_buffer=100\noutput=screen\nsearch=abc"
#define CONFIG_BAD_BUFFER "file=/tmp/\nengine=mc\naction=fetch\nlimit=1\nread_buffer=-100\noutput=screen\nsearch=123"
#define CONFIG_BAD_OUTPUT_EXISTS "file=/tmp/\nengine=mc\naction=fetch\nlimit=1\nread_buffer=100\noutput=/tmp/test1.conf"
#define CONFIG_BAD_OUTPUT_PERM "file=/tmp/\nengine=mc\naction=fetch\nlimit=1\nread_buffer=100\noutput=/etc/test.txt"

/**
 * Create the config filename
 */
void createConfigTest(char * filename, char * conf) {
	FILE *fp;
	fp = fopen(filename, "w+");
	fputs(conf, fp);
	fclose(fp);
}

/**
 */
int test_readConfig1() {
	int valid = 0;
	int result;
	struct config config;
	int errno;

	/* Create a file with custom text */
	createConfigTest(CONFIG_FILENAME, CONFIG_GOOD_1);

	errno = getConfig(CONFIG_FILENAME, &config);

	valid += assertTrue("test_readConfig1: The error should be 0", errno == STATUS_SUCCESS);

	valid += assertTrue("test_readConfig1: The config has 'action=scan'", strcmp(config.action, "scan") == 0);

	valid += assertTrue("test_readConfig1: The config has 'engine=mc'", strcmp(config.engine, "mc") == 0);

	valid += assertTrue("test_readConfig1: The config has 'search=str'", strcmp(config.search, "str") == 0);

	valid += assertTrue("test_readConfig1: The config has 'file=/tmp/", strcmp(config.file, "/tmp/") == 0);

	valid += assertTrue("test_readConfig1: The config has 'limit=1'", config.limit == 1);

	valid += assertTrue("test_readConfig1: The config has 'read_buffer=10'", config.read_buffer == 10);

	valid += assertTrue("test_readConfig1: The config has 'output=screen", strcmp(config.output, "screen") == 0);

	remove(CONFIG_FILENAME);

	return valid;
}

/**
 */
int test_readConfig2() {
	int valid = 0;
	int result;
	struct config config;
	int errno;

	// Create a file with custom text
	createConfigTest(CONFIG_FILENAME, CONFIG_GOOD_2);

	errno = getConfig(CONFIG_FILENAME, &config);

	valid += assertTrue("test_readConfig2: The error should be 0", errno == STATUS_SUCCESS);

	valid += assertTrue("test_readConfig2: The config has 'action=fetch'", strcmp(config.action, "fetch") == 0);

	valid += assertTrue("test_readConfig1: The config has 'engine=shm'", strcmp(config.engine, "shm") == 0);

	valid += assertTrue("test_readConfig1: The config has 'search=zzz'", strcmp(config.search, "zzz") == 0);

	valid += assertTrue("test_readConfig2: The config has 'file=/tmp/", strcmp(config.file, "/tmp/") == 0);

	valid += assertTrue("test_readConfig2: The config has 'limit=12'", config.limit == 12);

	valid += assertTrue("test_readConfig2: The config has 'read_buffer=100'", config.read_buffer == 100);

	valid += assertTrue("test_readConfig2: The config has 'output=/tmp/file.txt", strcmp(config.output, "/tmp/file.txt") == 0);

	remove(CONFIG_FILENAME);

	return valid;
}

/**
 */
int test_readBadConfig() {
	int valid = 0;
	int result;
	struct config config;
	int errno;

	errno = getConfig("/tmp/file_not_found.conf", &config);

	valid += assertTrue("test_readBadConfig: The error should be CONFIG_ERROR_FILE_READ", errno == CONFIG_ERROR_FILE_READ);

	// Bad action
	createConfigTest(CONFIG_FILENAME, CONFIG_BAD_ACTION);
	errno = getConfig(CONFIG_FILENAME, &config);
	valid += assertTrue("test_readBadConfig: The error should be CONFIG_ERROR_ACTION", errno == CONFIG_ERROR_ACTION);
	remove(CONFIG_FILENAME);

	// bad engine
	createConfigTest(CONFIG_FILENAME, CONFIG_BAD_ENGINE);
	errno = getConfig(CONFIG_FILENAME, &config);
	valid += assertTrue("test_readBadConfig: The error should be CONFIG_ERROR_ENGINE", errno == CONFIG_ERROR_ENGINE);
	remove(CONFIG_FILENAME);

	// bad search
	createConfigTest(CONFIG_FILENAME, CONFIG_BAD_SEARCH);
	errno = getConfig(CONFIG_FILENAME, &config);
	valid += assertTrue("test_readBadConfig: The error should be CONFIG_ERROR_SEARCH", errno == CONFIG_ERROR_SEARCH);
	remove(CONFIG_FILENAME);

	// Bad file
	createConfigTest(CONFIG_FILENAME, CONFIG_BAD_FILE);
	errno = getConfig(CONFIG_FILENAME, &config);
	valid += assertTrue("test_readBadConfig: The error should be CONFIG_ERROR_FILE", errno == CONFIG_ERROR_FILE);
	remove(CONFIG_FILENAME);

	// Bad limit
	createConfigTest(CONFIG_FILENAME, CONFIG_BAD_LIMIT);
	errno = getConfig(CONFIG_FILENAME, &config);
	valid += assertTrue("test_readBadConfig: The error should be CONFIG_ERROR_LIMIT", errno == CONFIG_ERROR_LIMIT);
	remove(CONFIG_FILENAME);

	// bad buffer
	createConfigTest(CONFIG_FILENAME, CONFIG_BAD_BUFFER);
	errno = getConfig(CONFIG_FILENAME, &config);
	valid += assertTrue("test_readBadConfig: The error should be CONFIG_ERROR_READ_BUFFER", errno == CONFIG_ERROR_READ_BUFFER);
	remove(CONFIG_FILENAME);

	// bad output
	createConfigTest(CONFIG_FILENAME, CONFIG_BAD_OUTPUT_PERM);
	errno = getConfig(CONFIG_FILENAME, &config);
	valid += assertTrue("test_readBadConfig: The error should NOT be STATUS_SUCCESS", errno != STATUS_SUCCESS);
	remove(CONFIG_FILENAME);

	// output file exists
	createConfigTest(CONFIG_FILENAME, CONFIG_BAD_OUTPUT_EXISTS);
	errno = getConfig(CONFIG_FILENAME, &config);
	valid += assertTrue("test_readBadConfig: The error should be CONFIG_ERROR_OUTPUT_FILE_EXISTS", errno == CONFIG_ERROR_OUTPUT_FILE_EXISTS);
	remove(CONFIG_FILENAME);

	return valid;
}

/**
 */
int test_knownParam() {
	int valid = 0;
	int result;
	struct config config;
	int errno;

	// valid

	result = knownParam("--action");
	valid += assertTrue("test_knownParam: Known param", result == STATUS_SUCCESS);

	result = knownParam("--engine");
	valid += assertTrue("test_knownParam: Known param", result == STATUS_SUCCESS);

	result = knownParam("--search");
	valid += assertTrue("test_knownParam: Known param", result == STATUS_SUCCESS);

	result = knownParam("--file");
	valid += assertTrue("test_knownParam: Known param", result == STATUS_SUCCESS);

	result = knownParam("--limit");
	valid += assertTrue("test_knownParam: Known param", result == STATUS_SUCCESS);

	result = knownParam("--read_buffer");
	valid += assertTrue("test_knownParam: Known param", result == STATUS_SUCCESS);

	result = knownParam("--output");
	valid += assertTrue("test_knownParam: Known param", result == STATUS_SUCCESS);

	// invalid

	result = knownParam("-output");
	valid += assertTrue("test_knownParam: Invalid param '-output'", result == STATUS_FAILURE);

	result = knownParam("-crap");
	valid += assertTrue("test_knownParam: Invalid param '-output'", result == STATUS_FAILURE);

	return valid;
}


/* Define UnitTests Lookup functions */

int getNumberTest() {
	return 4;
}

void getUnitTest(UnitTestFunction tests[], char *list[])
{
	int id = 0;

	tests[id]	= test_readConfig1;
	list[id++] = "test_readConfig1";

	tests[id]	= test_readConfig2;
	list[id++] = "test_readConfig2";

	tests[id]	= test_readBadConfig;
	list[id++] = "test_readBadConfig";

	tests[id]	= test_knownParam;
	list[id++] = "test_knownParam";

}
