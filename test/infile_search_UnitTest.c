
#define _XOPEN_SOURCE 500
#include <ftw.h>

#include "UnitTest.h"
#include "../util.h"
#include "../infile_search.h"

#define TEST_FILENAME "/tmp/index.html"
#define TEST_STRING "When 900 years old, you reach… Look as good, you will not.\nYou don’t know how hard I found it, signing the order to terminate your life\nIt's a trap!\nAren't you a little short for a storm trooper?\nThese aren’t the droids you’re looking for...\nTraveling through hyperspace ain't like dusting crops, farm boy.\nFear is the path to the dark side.\nI find your lack of faith disturbing.\nThere's always a bigger fish.\nGeneral Grievous, you're shorter than I expected.\nHelp me Obi-Wan Kenobi, you're my only hope.\nNo. I am your Father.\nObi-Wan has taught you well.\nOne thing's for sure, we're all going to be a lot thinner.\nYou may dispense with the pleasantries, Commander. I am here to put you back on schedule."


/**
 * Remove trace of tests
*/
int unlink_cb(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf) {
	int rv = remove(fpath);
	if (rv) {
		perror(fpath);
	}
	return rv;
}

int rmrf(char *path) {
	return nftw(path, unlink_cb, 64, FTW_DEPTH | FTW_PHYS);
}

/**
 * Create the test filename
 */
void createFileTest(char * filename) {

	FILE *fp;
	fp = fopen(filename, "w+");
	fputs(TEST_STRING, fp);
	fclose(fp);
}

/**
 */
int test_scanFile() {
	int valid = 0;
	int result;

	/* Create a file with custom text */
	createFileTest(TEST_FILENAME);

	result = scanFile(TEST_FILENAME, "the");
	valid += assertTrue("test_scanFile: The file has 'the'", result == 1);

	result = scanFile(TEST_FILENAME, "900");
	valid += assertTrue("test_scanFile: The file has '900'", result == 1);

	result = scanFile(TEST_FILENAME, "apu nahasapeemapetilon");
	valid += assertTrue("test_scanFile: The file does not have 'apu nahasapeemapetilon'", result == 0);

	remove(TEST_FILENAME);

	return valid;
}

/**
 */
int test_getListDir() {
	int valid = 0;
	int i = 0;
	int count = 0;
	struct stat st = {0};
	char *list[CONFIG_DEFAULT_LIMIT];

	char * paths[] = {
		"/tmp/test/",
		"/tmp/test/folder_1/",
		"/tmp/test/folder_1/abc1/",
		"/tmp/test/folder_2/",
		"/tmp/test/folder_2/abc2/"
	};
	char * files[] = {
		"/tmp/test/index.html",
		"/tmp/test/folder_1/index.html",
		"/tmp/test/folder_1/abc1/index.html",
		"/tmp/test/folder_2/index.html",
		"/tmp/test/folder_2/abc2/index.html"
	};

	for(; i < 5; ++i) {
		if (stat(paths[i], &st) == -1) {
			mkdir(paths[i], 0755);
			createFileTest((char *)files[i]);
		}
	}

	getDirList("/tmp", list, &count);

	valid += assertTrue("test_getListDir: The list has 5 files", count == 5);

	valid += assertTrue("test_getListDir: The last element is '/tmp/test/index.html'", strcmp(list[4], "/tmp/test/index.html") == 0);

	valid += assertTrue("test_getListDir: The 3rd element is '/tmp/test/folder_1/abc1/index.html'", strcmp(list[2], "/tmp/test/folder_2/index.html") == 0);

	// delete dir
	rmrf("/tmp/test");
	return valid;
}

/* Define UnitTests Lookup functions */

int getNumberTest() {
	return 2;
}

void getUnitTest(UnitTestFunction tests[], char *list[])
{
	int id = 0;

	tests[id]	= test_scanFile;
	list[id++] = "test_scanFile";

	tests[id]	= test_getListDir;
	list[id++] = "test_getListDir";
}
