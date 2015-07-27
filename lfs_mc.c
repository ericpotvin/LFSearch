#include "lfs_mc.h"

/**
 * Main
 */
int main(int argc, char *argv[]) {
	int result;
 	int action = ACTION_UNKNOWN;
	int type = TYPE_UNKNOWN;

	// Validate data
	result = validateInput(argc, argv);
	if(result != STATUS_SUCCESS) {
		showHelp(APP, DESCRIPTION);
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
