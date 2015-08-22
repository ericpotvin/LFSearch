#include "lfsearch.h"

/**
 * Main
 */
int main(int argc, char *argv[]) {
	int result;
	struct config conf;
	unsigned int valid;

	// Validate input/config file
	valid = validateInput(argc, argv);

	if(valid != STATUS_SUCCESS) {
		// showHelp?
	}

	// parse config/inputs
	
	if(DEBUG) {
		printf("DEBUG: Action is: %d\n", action);
		printf("DEBUG: Type is: %d\n", type);
		printf("DEBUG: Search is: %s\n", argv[2]);
		printf("DEBUG: File/Folder is: %s\n", argv[3]);
	}

	//
	// 
	//

	return 0;
}

/**
 */
unsigned int validateInput(int c, char * a) {

	int i = 0;
	int valid;
	struct config conf;

	if(c < 2) {
		return USER_INPUT_NO_INPUT;
	}

	// Config file
	if(hasConfileFile(c, a)) {
		valid = getConfig(a[2], conf);

		if(!valid) {
			return LFS_INVALID_CONFIG_FILE;
		}
	}

	for(; i < c; i+=2) {

		if(strcmp(a[i], "--config") == 0) {
			continue;
		}

		if(!knownParam(a[i])) {
			return LFS_UNKOWN_PARAM;
		}

		result = validateInputs(a[i], a[(i+1)]);
    if(result != STATUS_SUCCESS) {
			return result;
		}
	}
	
	return STATUS_SUCCESS;
}
