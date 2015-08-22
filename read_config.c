#include "util.h"
#include "read_config.h"

/**
 */
unsigned int getConfig(char * filename, struct config * conf) {

	FILE *file;
	char *s;
	char buffer[CONFIG_DEFAULT_BUFFER];
	char name[CONFIG_DEFAULT_BUFFER];
	char value[CONFIG_DEFAULT_BUFFER];
	uintmax_t num;

	if(!isFile(filename)) {
		return CONFIG_ERROR_FILE_READ;
	}

	file = fopen(filename, "r");
	if (file == NULL) {
		return CONFIG_ERROR_FILE_OPEN;
	}

	while ((s = fgets (buffer, sizeof buffer, file)) != NULL)
	{
		if (buffer[0] == '\n' || buffer[0] == '#') {
			continue;
		}

		s = strtok(buffer, CONFIG_DELIM);
		if (s == NULL) {
			continue;
		}
		strncpy(name, trim(s), CONFIG_DEFAULT_BUFFER);
		s = strtok(NULL, CONFIG_DELIM);
		if (s == NULL) {
			strncpy(value, "\0", CONFIG_DEFAULT_BUFFER);
		}
		else {
			strncpy(value, trim(s), CONFIG_DEFAULT_BUFFER);
		}

		// START FIELDS

		// action
		if(strcmp(name, CONFIG_STRUCT_ACTION) == 0) {
			strncpy((*conf).action, value, CONFIG_DEFAULT_BUFFER);
		}
		// engine
		else if(strcmp(name, CONFIG_STRUCT_ENGINE) == 0) {
			strncpy((*conf).engine, value, CONFIG_DEFAULT_BUFFER);
		}
		// search
		else if(strcmp(name, CONFIG_STRUCT_SEARCH) == 0) {
			strncpy((*conf).search, value, CONFIG_DEFAULT_BUFFER);
		}
		// file
		if(strcmp(name, CONFIG_STRUCT_FILE) == 0) {
			strncpy((*conf).file, value, CONFIG_DEFAULT_BUFFER);
		}
		// limit
		else if(strcmp(name, CONFIG_STRUCT_LIMIT) == 0) {
			if(strcmp(value, "") == 0) {
				(*conf).limit = CONFIG_DEFAULT_LIMIT;
			}
			else {
				num = strtoumax(value, NULL, 10);
				if (num == UINTMAX_MAX && errno == ERANGE) {
					(*conf).limit = CONFIG_DEFAULT_LIMIT;
				}
				else {
					(*conf).limit = num;
				}
			}
		}
		// buffer
		else if(strcmp(name, CONFIG_STRUCT_READ_BUFFER) == 0) {
			if(strcmp(value, "") == 0) {
				(*conf).read_buffer = CONFIG_DEFAULT_BUFFER;
			}
			else {
				num = strtoumax(value, NULL, 10);
				if (num == UINTMAX_MAX && errno == ERANGE) {
					(*conf).read_buffer = CONFIG_DEFAULT_BUFFER;
				}
				else {
					(*conf).read_buffer = num;
				}
			}
		}
		// output
		else if(strcmp(name, CONFIG_STRUCT_OUTPUT) == 0) {
			strncpy((*conf).output, value, CONFIG_DEFAULT_BUFFER);
		}
	}
	fclose(file);   

	return validateConfig(conf);
}

/**
 */
unsigned int knownParam(char * param) {

	if(strlen(param) < PARAM_PREFIX_COUNT) {
		return STATUS_FAILURE;
	}

	char * p = param + PARAM_PREFIX_COUNT;
	
	if(
		strcmp(p, CONFIG_STRUCT_ACTION) == 0 ||
		strcmp(p, CONFIG_STRUCT_ENGINE) == 0 ||
		strcmp(p, CONFIG_STRUCT_SEARCH) == 0 ||
		strcmp(p, CONFIG_STRUCT_FILE) == 0 ||
		strcmp(p, CONFIG_STRUCT_LIMIT) == 0 ||
		strcmp(p, CONFIG_STRUCT_READ_BUFFER) == 0 ||
		strcmp(p, CONFIG_STRUCT_OUTPUT) == 0
	) {
		return STATUS_SUCCESS;
	}

	return STATUS_FAILURE;
}

/**
 */
unsigned int validateConfig(struct config * conf) {

	int ret = 0;

	// action
	ret = validateActionInput((*conf).action);
	if(ret != STATUS_SUCCESS) {
		return ret;
	}

	// engine
	ret = validateEngineInput((*conf).engine);
	if(ret != STATUS_SUCCESS) {
		return ret;
	}

	// search
	ret = validateSearchInput((*conf).search);
	if(ret != STATUS_SUCCESS) {
		return ret;
	}

	// file
	ret = validateFileInput((*conf).file);
	if(ret != STATUS_SUCCESS) {
		return ret;
	}

	// limit
	ret = validateLimitInput((*conf).limit);
	if(ret != STATUS_SUCCESS) {
		return ret;
	}

	// read buffer
	ret = validateReadBufferInput((*conf).read_buffer);
	if(ret != STATUS_SUCCESS) {
		return ret;
	}

	// output
	ret = validateOutputInput((*conf).output);
	if(ret != STATUS_SUCCESS) {
		return ret;
	}

	return STATUS_SUCCESS;
}

/**
 */
unsigned int validateActionInput(char * value) {

	if(
		strcmp(value, CONFIG_VALID_ACTION_SCAN) == 0 ||
		strcmp(value, CONFIG_VALID_ACTION_EXISTS) == 0 ||
		strcmp(value, CONFIG_VALID_ACTION_FETCH) == 0 ||
		strcmp(value, CONFIG_VALID_ACTION_STORE) == 0 ||
		strcmp(value, CONFIG_VALID_ACTION_DELETE) == 0
	) {
		return STATUS_SUCCESS;
	}

	return CONFIG_ERROR_ACTION;
}

/**
 */
unsigned int validateEngineInput(char * value) {

	if(
		strcmp(value, CONFIG_VALID_ENGINE_MEMCACHE) == 0 ||
		strcmp(value, CONFIG_VALID_ENGINE_SHARED_MEM) == 0
	) {
		return STATUS_SUCCESS;
	}

	return CONFIG_ERROR_ENGINE;
}

/**
 */
unsigned int validateSearchInput(char * value) {

	if(strlen(value) > 0) {
		return STATUS_SUCCESS;
	}

	return CONFIG_ERROR_SEARCH;
}

/**
 */
unsigned int validateFileInput(char * value) {

	if(isDir(value) || isFile(value)) {
		return STATUS_SUCCESS;
	}

	return CONFIG_ERROR_FILE;
}

/**
 */
unsigned int validateLimitInput(int value) {

	if(value < 1 || value > CONFIG_DEFAULT_LIMIT) {
		return CONFIG_ERROR_LIMIT;
	}

	return STATUS_SUCCESS;
}

/**
 */
unsigned int validateReadBufferInput(int value) {

	if(value < 1 || value > CONFIG_DEFAULT_BUFFER) {
		return CONFIG_ERROR_READ_BUFFER;
	}

	return STATUS_SUCCESS;
}

/**
 */
unsigned int validateOutputInput(char * value) {

	if(strcmp(value, CONFIG_VALID_OUTPUT_SCREEN) == 0) {
		return STATUS_SUCCESS;
	}

	if(isFile(value)) {
		return CONFIG_ERROR_OUTPUT_FILE_EXISTS;
	}

	/* TODO: make this a function */
	char * path = dirname(strdup(value));
	int rval;

	/* Check file existence. */
	rval = access(path, F_OK);
	if(rval != 0) {
		return errno;
	}

	/* Check read access. */
	rval = access(path, R_OK);
	if(rval != 0) {
		return errno;
	}

	/* Check write access. */
	rval = access(path, W_OK);
	if (rval != 0) {
		return errno;
	}

	return STATUS_SUCCESS;
}
