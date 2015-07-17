# # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
# BinaryTree Makefile
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # #

# Which compile t use
CC = gcc

# compiler flags:
# -I	Include path
# -O	slow compile but fast execution
# -g	adds debugging information to the executable file
# -Wall turns on most, but not all, compiler warnings
FLAGS = -I../. -O -g -Wall

# Program name
UNITTEST = UnitTest

# Source files
SOURCE = $(UNITTEST).c

default: all

all: infile_search shared_memory util

infile_search:
	$(CC) $(CFLAGS) -o infile_search_test ../util.c ../infile_search.c infile_search_$(UNITTEST).c $(SOURCE) -lcrypto -lssl 

shared_memory:
	$(CC) $(CFLAGS) -o shared_memory_test ../util.c ../shared_memory.c shared_memory_$(UNITTEST).c $(SOURCE) -lcrypto -lssl -lrt

util:
	$(CC) $(CFLAGS) -o util_test ../util.c util_$(UNITTEST).c $(SOURCE) -lcrypto -lssl

clean:
	-rm -f util_test infile_search_test shared_memory_test
