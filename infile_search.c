#include "util.h"
#include "infile_search.h"

/**
 */
unsigned int scanFile(char * filename, char * searchString) {

	FILE *fp;
	int lineNumber = 0;
	int numberOfResult = 0;
	char currentStr[INFILE_SEARCH_DEFAULT_MAX_CHAR];

	if(!isFile(filename)) {
		return STATUS_FAILURE;
	}

	if((fp = fopen(filename, "r")) == NULL) {
		return STATUS_FAILURE;
	}

	while(fgets(currentStr, INFILE_SEARCH_DEFAULT_MAX_CHAR, fp) != NULL) {
		lineNumber++;
		if((strstr(currentStr, searchString)) != NULL) {
			printf("%s [%d]: %s\n", filename, lineNumber, trim(currentStr));
			numberOfResult++;
		}
	}

	if(fp) {
		fclose(fp);
	}

	if(DEBUG) {
		printf("DEBUG: Found %d occurence of %s in %s\n", numberOfResult, searchString, filename);
	}

	return numberOfResult > 0 ? STATUS_SUCCESS : STATUS_FAILURE;
}

/**
 */
void getDirList(char * root, char * list[], int * count) {

	DIR *dir;
	struct dirent *entry;

	dir = opendir(root);
	if(!dir) {
		return;
	}
	if(*count >= CONFIG_DEFAULT_LIMIT) {
		closedir(dir);
		return;
	}

	while ((entry = readdir(dir)) != NULL) {
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
			continue;
		}
		if(entry->d_type == DT_DIR) {
			char path[INFILE_SEARCH_DEFAULT_MAX_CHAR];
			int len = snprintf(path, sizeof(path)-1, "%s/%s", root, entry->d_name);
			if(DEBUG) {
				printf("DEBUG: Found Path: %s\n", path);
			}
			getDirList(path, list, count);
		}
		else if(entry->d_type == DT_REG && strcmp(entry->d_name, INFILE_SEARCH_DEFAULT_FILENAME) == 0) {
			char file[INFILE_SEARCH_DEFAULT_MAX_CHAR];
			snprintf(file, sizeof(file)-1, "%s/%s", root, entry->d_name);
			if(DEBUG) {
				printf("DEBUG: Found File: %s\n", file);
			}
	    list[(*count)] = strdup(file);
			(*count)++;
			if((*count) >= CONFIG_DEFAULT_LIMIT) {
				return;
			}
		}
	}
	closedir(dir);
}
