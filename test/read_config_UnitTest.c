#include "UnitTest.h"
#include "../util.h"
#include "../read_config.h"

#define CONFIG_FILENAME "/tmp/test1.conf"

/**
 * Create the config filename
 */
void createConfigTest(char * filename) {
	FILE *fp;
	fp = fopen(filename, "w+");
	fputs("action=test\n", fp);
	fputs("limit=1\n", fp);
	fputs("#comment on line 3", fp);
	fclose(fp);
}

/**
 */
int test_readConfig() {
	int valid = 0;
	int result;
	struct config config;
	int errno;

	/* Create a file with custom text */
	createConfigTest(CONFIG_FILENAME);

	errno = getConfig(CONFIG_FILENAME, &config);

	valid += assertTrue("test_readConfig: The config has 'action=test'", strcmp(config.action, "test") == 0);

	valid += assertTrue("test_readConfig: The config 'string' should not equal 'xyz'", config.limit == 1);

	valid += assertTrue("test_readConfig: The config 'string' should not equal 'xyz'", (config.limit == 12) == 0);

	valid += assertTrue("test_readConfig: The error should be 0", errno == STATUS_SUCCESS);

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

	valid += assertTrue("test_readConfig: The error should be CONFIG_ERROR_FILE_READ", errno == CONFIG_ERROR_FILE_READ);

	return valid;
}

/* Define UnitTests Lookup functions */

int getNumberTest() {
	return 2;
}

void getUnitTest(UnitTestFunction tests[], char *list[])
{
	int id = 0;

	tests[id]	= test_readConfig;
	list[id++] = "test_readConfig";

	tests[id]	= test_readBadConfig;
	list[id++] = "test_readBadConfig";
}
