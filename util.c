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
	printf("  To Get data (get data from shared memory):\n");
	printf("     %s get <search> <file_or_folder>\n\n", app);
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

/**
 */
unsigned int validateInput(int argc, char *argv[]) {
	int action;

	// Validate the number of params first
	if (argc < 3 || argc > 5) {
		return INPUT_BAD_PARAM;
	}

	return STATUS_SUCCESS;
}

/**
 */
unsigned int validateAction(char *val, int * action) {
	if (strcmp(val, "scan") == 0) {
		(*action) = ACTION_SCAN;
		return STATUS_SUCCESS;
	}
	if (strcmp(val, "exists") == 0) {
		(*action) = ACTION_EXISTS;
		return STATUS_SUCCESS;
	}
	if (strcmp(val, "get") == 0) {
		(*action) = ACTION_GET;
		return STATUS_SUCCESS;
	}
	if (strcmp(val, "store") == 0) {
		(*action) = ACTION_STORE;
		return STATUS_SUCCESS;
	}
	if (strcmp(val, "delete") == 0) {
		(*action) = ACTION_DELETE;
		return STATUS_SUCCESS;
	}
	return STATUS_FAILURE;
}

/**
 * Get the type (File or Dir)
 */
unsigned int getFileType(char * file, int * type) {
	if(isFile(file)) {
		(*type) = TYPE_FILE;
		return STATUS_SUCCESS;
	}
	if(isDir(file)) {
		(*type) = TYPE_DIR;
		return STATUS_SUCCESS;
	}
	return STATUS_FAILURE;
}
