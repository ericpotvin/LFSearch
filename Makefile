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

# Program name
PROGRAM = lfsearch

# Source files
SOURCE = *.c

default: unittest

unittest: $(PROGRAM).c
	$(CC) $(CFLAGS) -o $(PROGRAM) $(SOURCE) -lcrypto -lssl -lrt

clean:
	-rm -f $(PROGRAM)
