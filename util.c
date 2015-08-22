#include "util.h"

/**
 */
char *trim(char *str) {

	// ltrim
	while(isspace(*str)) {
		str++;
	}

	if(*str == 0) {
		return str;
	}

	// rtrim
	char * back = str + strlen(str);
	while(isspace(*--back));
	*(back+1) = '\0';
	return str;
}

/**
 * Show Help
 */
void showHelp(char * app, char * method) {
	printf("\n%s Version %s\n", app, VERSION);
	printf("\nLocate File Search using %s cache.\n", method);
	printf("\nUsage:\n\n");
	printf("  To Scan data (scan file system):\n");
	printf("     %s scan <search> <file_or_folder>\n\n", app);
	printf("  To Fetch data (fetch data from shared memory):\n");
	printf("     %s fetch <engine> <search> <file_or_folder>\n\n", app);
	printf("  To Check if a search exists:\n");
	printf("     %s exists <search>\n\n", app);
	printf("  To Store data:\n");
	printf("     %s store <search> <file_or_folder>\n\n", app);
	printf("  To Delete data:\n");
	printf("     %s delete <search>\n\n", app);
}

/**
 */
void exitProgram(int err, char * msg) {
	if(DEBUG) {
		printf("ERROR: %s\n", msg);
	}
	exit(err);
}

/**
 */
unsigned int isFile(char * file) {
	struct stat f;
	return stat(file, &f) == 0 && S_ISREG(f.st_mode);
}
 
/**
 */
unsigned int isDir(char * dir) {
	struct stat f;
	return stat(dir, &f) == 0 && S_ISDIR(f.st_mode);
}

/**
 */
char * getMD5(char * string) {

	int i = 0;
	unsigned char md5Str[MD5_DIGEST_LENGTH];
	char *ret = (char*)malloc(33);

	MD5(string, strlen(string), md5Str);

	for(; i < 16; ++i) {
		sprintf(&ret[i*2], "%02x", (unsigned int)md5Str[i]);
	}
	return ret;
}
