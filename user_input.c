#include "util.h"
#include "user_input.h"

/**
 */
unsigned int hasConfileFile(int c, char * a[]) {

	int i = 1;

	for(; i < c; i+=2) {

		if(strcmp(a[i], "--config") == 0 && isFile(a[(i+1)])) {
			return STATUS_SUCCESS;
		}
	}

	return USER_INPUT_NO_CONFIG_FOUND;
}

/**
 */
unsigned int validateInputs(char * param, char * value) {

	char * p = param + PARAM_PREFIX_COUNT;

	if(strcmp(p, CONFIG_STRUCT_ACTION) == 0) {
		return validateActionInput(value);
	}

	if(strcmp(p, CONFIG_STRUCT_ENGINE) == 0) {
		return validateEngineInput(value);
	}

	if(strcmp(p, CONFIG_STRUCT_SEARCH) == 0) {
		return validateSearchInput(value);
	}

	if(strcmp(p, CONFIG_STRUCT_FILE) == 0) {
		return validateFileInput(value);
	}

	if(strcmp(p, CONFIG_STRUCT_LIMIT) == 0) {
		return validateLimitInput(value);
	}

	if(strcmp(p, CONFIG_STRUCT_READ_BUFFER) == 0) {
		return validateReadBufferInput(value);
	}

	if(strcmp(p, CONFIG_STRUCT_OUTPUT) == 0) {
		return validateOutputInput(value);
	}

	return STATUS_FAILURE;
}

