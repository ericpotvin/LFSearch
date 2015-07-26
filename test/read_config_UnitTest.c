#include "UnitTest.h"
#include "../util.h"
#include "../read_config.h"

#define CONFIG_FILENAME "/tmp/test1.conf"

#define CONFIG_GOOD_1 "search_dir=/tmp/\naction=scan\nlimit=1\nread_buffer=10\noutput=screen\nsearch_file="
#define CONFIG_GOOD_2 "search_dir=/tmp/\naction=get\nlimit=12\nread_buffer=100\noutput=file\nsearch_file=test.txt"

#define CONFIG_BAD_DIR "search_dir=/not_found_tmp/\naction=get\nlimit=1\nread_buffer=100\noutput=file"
#define CONFIG_BAD_ACTION "search_dir=/tmp/\naction=list\nlimit=12\nread_buffer=100\noutput=file"
#define CONFIG_BAD_LIMIT "search_dir=/tmp/\naction=get\nlimit=-1\nread_buffer=100\noutput=file"
#define CONFIG_BAD_BUFFER "search_dir=/tmp/\naction=get\nlimit=1\nread_buffer=-100\noutput=file"
#define CONFIG_BAD_OUTPUT "search_dir=/tmp/\naction=get\nlimit=1\nread_buffer=100\noutput=xml"

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

	valid += assertTrue("test_readConfig1: The config has 'action=scan'", strcmp(config.action, "scan") == 0);

	valid += assertTrue("test_readConfig1: The config has 'limit=1'", config.limit == 1);

	valid += assertTrue("test_readConfig1: The config has 'read_buffer=10'", config.read_buffer == 10);

	valid += assertTrue("test_readConfig1: The config has 'search_dir=/tmp/", strcmp(config.search_dir, "/tmp/") == 0);

	valid += assertTrue("test_readConfig1: The config has 'output=screen", strcmp(config.output, "screen") == 0);

	valid += assertTrue("test_readConfig1: The config has 'search_file=index.html", strcmp(config.search_file, "index.html") == 0);

	valid += assertTrue("test_readConfig1: The error should be 0", errno == STATUS_SUCCESS);

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

	/* Create a file with custom text */
	createConfigTest(CONFIG_FILENAME, CONFIG_GOOD_2);

	errno = getConfig(CONFIG_FILENAME, &config);

	valid += assertTrue("test_readConfig2: The config has 'action=get'", strcmp(config.action, "get") == 0);

	valid += assertTrue("test_readConfig2: The config has 'limit=12'", config.limit == 12);

	valid += assertTrue("test_readConfig2: The config has 'read_buffer=100'", config.read_buffer == 100);

	valid += assertTrue("test_readConfig2: The config has 'search_dir=/tmp/", strcmp(config.search_dir, "/tmp/") == 0);

	valid += assertTrue("test_readConfig2: The config has 'output=screen", strcmp(config.output, "file") == 0);

	valid += assertTrue("test_readConfig2: The error should be 0", errno == STATUS_SUCCESS);

	valid += assertTrue("test_readConfig1: The config has 'search_file=test.txt", strcmp(config.search_file, "test.txt") == 0);

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

	/* Bad dir */
	createConfigTest(CONFIG_FILENAME, CONFIG_BAD_DIR);
	errno = getConfig(CONFIG_FILENAME, &config);
	valid += assertTrue("test_readBadConfig: The error should be CONFIG_ERROR_BAD_CONFIG_DIR", errno == CONFIG_ERROR_BAD_CONFIG_DIR);
	remove(CONFIG_FILENAME);

	/* Bad action */
	createConfigTest(CONFIG_FILENAME, CONFIG_BAD_ACTION);
	errno = getConfig(CONFIG_FILENAME, &config);
	valid += assertTrue("test_readBadConfig: The error should be CONFIG_ERROR_BAD_CONFIG_ACTION", errno == CONFIG_ERROR_BAD_CONFIG_ACTION);
	remove(CONFIG_FILENAME);

	/* Bad limit */
	createConfigTest(CONFIG_FILENAME, CONFIG_BAD_LIMIT);
	errno = getConfig(CONFIG_FILENAME, &config);
	valid += assertTrue("test_readBadConfig: The error should be CONFIG_ERROR_BAD_CONFIG_LIMIT", errno == CONFIG_ERROR_BAD_CONFIG_LIMIT);
	remove(CONFIG_FILENAME);

	/* bad buffer */
	createConfigTest(CONFIG_FILENAME, CONFIG_BAD_BUFFER);
	errno = getConfig(CONFIG_FILENAME, &config);
	valid += assertTrue("test_readBadConfig: The error should be CONFIG_ERROR_BAD_CONFIG_BUFFER", errno == CONFIG_ERROR_BAD_CONFIG_BUFFER);
	remove(CONFIG_FILENAME);

	/* bad buffer */
	createConfigTest(CONFIG_FILENAME, CONFIG_BAD_OUTPUT);
	errno = getConfig(CONFIG_FILENAME, &config);
	valid += assertTrue("test_readBadConfig: The error should be CONFIG_ERROR_BAD_CONFIG_OUTPUT", errno == CONFIG_ERROR_BAD_CONFIG_OUTPUT);
	remove(CONFIG_FILENAME);

	return valid;
}

/* Define UnitTests Lookup functions */

int getNumberTest() {
	return 3;
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

}
