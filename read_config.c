#include "util.h"
#include "read_config.h"

/**
 */
unsigned int getConfig(char * filename, struct config * conf) {

	FILE *file;
	char *s;
	char buffer[CONFIG_BUFFER];
	char name[CONFIG_BUFFER];
	char value[CONFIG_BUFFER];

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
		strncpy(name, trim(s), CONFIG_BUFFER);
		s = strtok(NULL, CONFIG_DELIM);
		if (s == NULL) {
			continue;
		}
		strncpy(value, trim(s), CONFIG_BUFFER);

		if(strcmp(name, CONFIG_STRUCT_SEARCH_DIR) == 0) {
			strncpy((*conf).search_dir, value, CONFIG_BUFFER);
		}
		else if(strcmp(name, CONFIG_STRUCT_ACTION) == 0) {
			strncpy((*conf).action, value, CONFIG_BUFFER);
		}
		else if(strcmp(name, CONFIG_STRUCT_LIMIT) == 0) {
			(*conf).limit = atoi(value);
		}
		else if(strcmp(name, CONFIG_STRUCT_READ_BUFFER) == 0) {
			(*conf).read_buffer = atoi(value);
		}
		else if(strcmp(name, CONFIG_STRUCT_OUTPUT) == 0) {
			strncpy((*conf).output, value, CONFIG_BUFFER);
		}
	}
	fclose(file);   

	return validateConfig(conf);
}

/**
 */
unsigned int validateConfig(struct config * conf) {

	if(!isDir((*conf).search_dir)) {
		return CONFIG_ERROR_BAD_CONFIG_DIR;
	}

	if(
		strcmp((*conf).action, CONFIG_VALID_ACTION_SCAN) != 0 &&
		strcmp((*conf).action, CONFIG_VALID_ACTION_GET) != 0
	) {
		return CONFIG_ERROR_BAD_CONFIG_ACTION;
	}

	if((*conf).limit <= 0) {
		return CONFIG_ERROR_BAD_CONFIG_LIMIT;
	}

	if((*conf).read_buffer <= 0) {
		return CONFIG_ERROR_BAD_CONFIG_BUFFER;
	}

	if(
		strcmp((*conf).output, CONFIG_VALID_OUTPUT_SCREEN) != 0 &&
		strcmp((*conf).output, CONFIG_VALID_OUTPUT_FILE) != 0
	) {
		return CONFIG_ERROR_BAD_CONFIG_OUTPUT;
	}

	return STATUS_SUCCESS;
}
