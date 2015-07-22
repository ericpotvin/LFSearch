#include "util.h"
#include "shared_memory.h"

/**
 */
unsigned int shmExists(char * key) {

	unsigned int result;
	char * data;

	result = shmFetch(key, &data);

	if(result != 0) {
		return SHM_ERROR_NOT_FOUND;
	}

	if(strcmp(data, "") != 0) {
		return SHM_ERROR_FOUND;
	}
	return SHM_ERROR_NOT_FOUND;
}

/**
 */
unsigned int shmStore(char * key, char * data) {

	int shm;
	size_t	len;
	char *addr;

	len = strlen(data);

	if(DEBUG) {
		printf("DEBUG: Storing %d bytes of data for key '%s'\n", (int)len, key);
	}

	shm = shm_open(key,	O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);

	if(shm == -1) {
		return SHM_ERROR_OPEN;
	}

	ftruncate(shm ,len);
	if(shm == -1) {
		return SHM_ERROR_TRUNCATE;
	}

	addr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED , shm, 0);

	if(addr == MAP_FAILED) {
		close(shm);
		return SHM_ERROR_MMAP;
	}

	close(shm);

	if(DEBUG) {
		printf("DEBUG: Copying %d bytes data to memory\n", (int)len);
	}
 
	memcpy(addr, data, len);
	// Don't forget to free the mmapped memory

	if (munmap(addr, len) == -1) {
			return SHM_ERROR_MUNMAP;
	}

	return STATUS_SUCCESS;
}

/**
 */
unsigned int shmFetch(char * key, char ** data) {

	int shm;
	int s;
	struct stat f;

	shm = shm_open(key,	O_RDWR | O_EXCL, 0);

	if(shm == -1) {
		return SHM_ERROR_OPEN;
	}

	s = fstat(shm , &f);

	if(s == -1) {
		return SHM_ERROR_STAT;
	}

	(*data) = mmap(NULL, f.st_size, PROT_READ | PROT_WRITE, MAP_SHARED , shm, 0);

	if((*data) == MAP_FAILED) {
		close(shm);
		return SHM_ERROR_MMAP;
	}

	close(shm);

	return STATUS_SUCCESS;
}

/**
 */
unsigned int shmDelete(char * key) {
	int result;

	result = shm_unlink(key);
	if(result == -1) {
		return SHM_ERROR_DELETE;
	}

	return STATUS_SUCCESS;
}
