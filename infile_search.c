#include "util.h"
#include "infile_search.h"

/**
 */
unsigned int scanFile(char * filename, char * searchString) {

	FILE *fp;
	int lineNumber = 0;
	int numberOfResult = 0;
	char currentStr[INFILE_SEARCH_MAX_CHAR_READ];

	if(!isFile(filename)) {
		return 0;
	}

	if((fp = fopen(filename, "r")) == NULL) {
		return 0;
	}

	while(fgets(currentStr, INFILE_SEARCH_MAX_CHAR_READ, fp) != NULL) {
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

	return numberOfResult > 0;
}

/**
 */
unsigned int scanDir(char * root, char * searchString) {
	DIR *dir;
	struct dirent *entry;

	dir = opendir(root);
	if(!dir) {
		return INFILE_SEARCH_ERROR_OPENDIR;
	}
	entry = readdir(dir);
	if(!entry) {
		return INFILE_SEARCH_ERROR_READDIR;
	}

	do {
		if (entry->d_type == DT_DIR) {
			if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
				continue;
			}
			char path[1024];
			int len = snprintf(path, sizeof(path)-1, "%s/%s", root, entry->d_name);
			path[len] = 0;
			scanDir(path, searchString);
		}
		else if(strcmp(entry->d_name, INFILE_SEARCH_HAYSTACK) == 0) {
			char file[1024];
			snprintf(file, sizeof(file)-1, "%s/%s", root, entry->d_name);
			scanFile(file, searchString);
		}
	}
	while (entry = readdir(dir));

	closedir(dir);

	return 0;
}

