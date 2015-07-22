#ifndef DEFINE_H
#define DEFINE_H

/* common */

#define VERSION "0.1"

#ifndef DEBUG 
	#define DEBUG 0
#endif

/* status */

#define STATUS_FAILURE 1
#define STATUS_SUCCESS 0

/* Inputs */

#define INPUT_BAD_PARAM 10

/* actions */

#define ACTION_INVALID 100
#define ACTION_GET 101
#define ACTION_STORE 102
#define ACTION_DELETE 103
#define ACTION_EXISTS 104
#define ACTION_SCAN 105

/* file type */

#define TYPE_UNKNOWN 200
#define TYPE_FILE 201
#define TYPE_DIR 202

/* shared memory */

#define SHM_MAX_SHARED_MEMORY_SIZE 1024
#define SHM_ERROR_OPEN 301
#define SHM_ERROR_TRUNCATE 302
#define SHM_ERROR_MMAP 303
#define SHM_ERROR_STAT 304
#define SHM_ERROR_DELETE 305
#define SHM_ERROR_FETCH 306
#define SHM_ERROR_MUNMAP 307
#define SHM_ERROR_NOT_FOUND 308
#define SHM_ERROR_FOUND 309

/* infile search */

#define INFILE_SEARCH_MAX_CHAR_READ 1024
#define INFILE_SEARCH_HAYSTACK "index.html"

#define INFILE_SEARCH_ERROR_OPENDIR 401
#define INFILE_SEARCH_ERROR_READDIR 402

/* read config */

#define CONFIG_DELIM "="
#define CONFIG_BUFFER 256

#define CONFIG_ERROR_FILE_READ 501
#define CONFIG_ERROR_FILE_OPEN 502

/* END */

#endif
