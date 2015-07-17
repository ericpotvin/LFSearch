#include "lfsearch.h"

/**
 * Main
 */
int main(int argc, char *argv[]) {
	int result;
 	int action = ACTION_INVALID;
	int type = TYPE_UNKNOWN;

	// Validate data
	result = validateInput(argc, argv);
	if(result != STATUS_SUCCESS) {
		showHelp();
		exitProgram(result, "Invalid Input");
	}

	// Get the action
	result = validateAction(argv[1], &action);
	if(result != STATUS_SUCCESS) {
		exitProgram(result, "Invalid Action");
	}

	// Get the type
	if(action == ACTION_SCAN || action == ACTION_STORE) {
		result = getFileType(argv[3], &type);
		if(result != STATUS_SUCCESS) {
			exitProgram(result, "File/Folder not found");
		}
	}
	else {
		argv[3] = "";
	}

	//
	// 
	//

	if(DEBUG) {
		printf("DEBUG: Action is: %d\n", action);
		printf("DEBUG: Type is: %d\n", type);
		printf("DEBUG: Search is: %s\n", argv[2]);
		printf("DEBUG: File/Folder is: %s\n", argv[3]);
	}

	// Need to code after testing done

	return 0;
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
