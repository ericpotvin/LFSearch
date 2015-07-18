# # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
# Makefile
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # #

# Which compile t use
CC = gcc

# compiler flags:
# -I	Include path
# -O	slow compile but fast execution
# -g	adds debugging information to the executable file
# -Wall turns on most, but not all, compiler warnings
FLAGS = -I./ -O -g -Wall 

# Required files for both app
SOURCE = infile_search.c util.c 

default: all 

all: lfs_shm lfs_mc

lfs_shm: 
	$(CC) $(CFLAGS) -o lfs_shm lfs_shm.c shared_memory.c $(SOURCE) -lcrypto -lssl -lrt

lfs_mc: 
	$(CC) $(CFLAGS) -o lfs_mc lfs_mc.c memcached.c $(SOURCE) -lcrypto -lmemcached -lpthread

clean:
	-rm -f lfs_shm lfs_mc
