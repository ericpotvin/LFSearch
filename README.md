# Local File Search

## Prerequisite

* libmemcached >= 1.0.18
* libsasl2-dev >= libsasl2.so.2.0.25

## Install

### libmemcached

Download the version from https://launchpad.net/libmemcached

	./configure
	make
	sudo make install

### memcached

	sudo apt-get install memcached

### sasl2

	sudo apt-get install libsasl2-dev

### LD_LIBRARY_PATH

if:

	echo $LD_LIBRARY_PATH

return nothing, then add the LD_LIBRARY_PATH to your ~/.bashrc. For example:

	export LD_LIBRARY_PATH=/usr/local/lib

## Build

To build run:

	make

This will create both app:

* lfs_shm: Local file search using shared memory
* lfs_mc: Local file search using memcached

To build unit tests:

	cd test/
	make

## Shared Memory

By default, the shared memory size is 32 MB. To check, simply run:

	cat /proc/sys/kernel/shmmax 

This will return:

	33554432

Meaning each segment size will be 32k. 

	ipcs -lm 
	
	------ Shared Memory Limits --------
	max number of segments = 4096
	max seg size (kbytes) = 32768
	max total shared memory (kbytes) = 8388608
	min seg size (bytes) = 1

If you want to increase the each segments, you can setup the new size in the /etc/sysctl.conf:

For example, if you want to increase it to 128MB:

	kernel.shmmax=134217728

Then run:

	sysctl -p

Now, if you run the ipcs command you will see the new size of each segments:

	ipcs -lm

	------ Shared Memory Limits --------
	max number of segments = 4096
	max seg size (kbytes) = 131072
	max total shared memory (kbytes) = 8388608
	min seg size (bytes) = 1

## Config file

A Config file can be specified to allow parameters to be parse automatically.

### search_dir:

This allow the script to use a default search path.

eg:

	search_dir=/usr/share/base-files/

### action:

This allow the script to use a default action.

eg:

	action=scan

### limit

This will limit the number of records processed by the script

eg:

	limit=100

### read_buffer

This will limit the size (bytes) of the buffer read when looking for a string in a file.

eg:

	read_buffer=1024
