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

		// search dir
		if(strcmp(name, CONFIG_STRUCT_SEARCH_DIR) == 0) {
			strncpy((*conf).search_dir, value, CONFIG_DEFAULT_BUFFER);
		}
		// action
		else if(strcmp(name, CONFIG_STRUCT_ACTION) == 0) {
			strncpy((*conf).action, value, CONFIG_DEFAULT_BUFFER);
		}
		// limit
		else if(strcmp(name, CONFIG_STRUCT_LIMIT) == 0) {
			if(strcmp(value, "") == 0) {
				(*conf).limit = CONFIG_DEFAULT_LIMIT;
			}
			else {
				(*conf).limit = atoi(value);
			}
		}
		// buffer
		else if(strcmp(name, CONFIG_STRUCT_READ_BUFFER) == 0) {
			if(strcmp(value, "") == 0) {
				(*conf).read_buffer = CONFIG_DEFAULT_BUFFER;
			}
			else {
				(*conf).read_buffer = atoi(value);
			}
		}
		// output
		else if(strcmp(name, CONFIG_STRUCT_OUTPUT) == 0) {
			strncpy((*conf).output, value, CONFIG_DEFAULT_BUFFER);
		}
		// search file
		else if(strcmp(name, CONFIG_STRUCT_SEARCH_FILE) == 0) {
			if(strcmp(value, "") == 0) {
				strncpy((*conf).search_file, INFILE_SEARCH_DEFAULT_FILENAME, CONFIG_DEFAULT_BUFFER);
			}
			else {
				strncpy((*conf).search_file, value, CONFIG_DEFAULT_BUFFER);
			}
		}
	}
	fclose(file);   

	return validateConfig(conf);
}

/**
 */
unsigned int validateConfig(struct config * conf) {

	// search dir
	if(!isDir((*conf).search_dir)) {
		return CONFIG_ERROR_BAD_CONFIG_DIR;
	}

	// action
	if(
		strcmp((*conf).action, CONFIG_VALID_ACTION_SCAN) != 0 &&
		strcmp((*conf).action, CONFIG_VALID_ACTION_GET) != 0
	) {
		return CONFIG_ERROR_BAD_CONFIG_ACTION;
	}

	// limit
	if((*conf).limit < 0) {
		return CONFIG_ERROR_BAD_CONFIG_LIMIT;
	}

	// buffer
	if((*conf).read_buffer < 0) {
		return CONFIG_ERROR_BAD_CONFIG_BUFFER;
	}

	// output
	if(
		strcmp((*conf).output, CONFIG_VALID_OUTPUT_SCREEN) != 0 &&
		strcmp((*conf).output, CONFIG_VALID_OUTPUT_FILE) != 0
	) {
		return CONFIG_ERROR_BAD_CONFIG_OUTPUT;
	}

	return STATUS_SUCCESS;
}
