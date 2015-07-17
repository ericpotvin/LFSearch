#include "define.h"

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
//#include <ftw.h>
#include <openssl/md5.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <sys/file.h>
#include <sys/ipc.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <unistd.h>

/**
 * trim()
 * Trim a string
 *
 * Source: http://stackoverflow.com/questions/656542/trim-a-string-in-c
 * Input: (Char*) str: The String
 * Return: String
 */
char * trim(char *str);

/**
 * showHelp()
 * Show the program help
 */
void showHelp();

/**
 * exitProgram()
 * Stop program due to error
 *
 * Input: (int) err: The error code
 * Input: (Char*) str: The Message to display
 */
void exitProgram(int err, char * msg);

/**
 * isFile()
 * Check if the file is a file
 *
 * Input: (Char*) file: The full path of the file
 * Return: Int
 */
unsigned int isFile(char * file);

/**
 * isDir()
 * Check if the file is a directory
 *
 * Input: (Char*) dir: The full path of the dir
 * Return: Int
 */
unsigned int isDir(char * dir);

/**
 * getMD5()
 * Get the MD5 of a string
 *
 * Input: (Char*) string: The string
 * Input: (Char*) md5: The md5 string
 */
char * getMD5(char * string);
