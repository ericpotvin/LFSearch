# Local File Search

Local File Search is a simple tool that allow you to search for a specific string inside files in a folder recursively.

This tool allows also to cache results either using shared memory or memcached.

LFS requires either 4 arguments or a config file.

## Parameters

"lfsearch" requires paramters in order to succesfully fetch and/or store results.

### Actions:

The "action" param is used to determine what type of operation the tool will execute.

**This param is always required.**

The param is: `--action`

The allowed values are:

* scan

"scan" will look for a string in files without using any caching mechanism.

* fetch

"fetch" will retrive the data from memory.

* exists

"exsits" will check if a search string exists in memory.

* store

"store" will store the result of a search in memory.

* delete

"delete" will delete the data from memory.

Note: parameters can be saved in a config file for faster usage.

### Engine:

This tells to the tool which memory engine it will use for performing the entended operations.

**The "engine" is required for "fetch, exists, store and delete".**

The param is: `--engine`

The allowed values are:

* mc

If you want to use memcached

* shm

If you want to use shared memory

* rds

If you want to use redis

### Search String

This is your search string.

**This param is always required.**

The param is: `--search`

### Path or file

The full path of the files you want to parse, or the full filename location.

**This param is always required for store and scan only.**

The param is: `--file`

### Limit

Set the number of record to fetch for a search.

**This param is optional.**

The param is: `--limit`

### Read Buffer

Set the read buffer to search.

**This param is optional.**

The param is: `--readbuffer`

### Output

Set the output for a search.

**This param is optional.**

The param is: `--output`

The allowed values are:

* screen

If you want to display the result

* /path/to/file

If you want to save the result to a file. This needs to be a valid filename with write permissions

### Config file

The config file will allow you to use all parameters (except this one) into a single file.

The param is: `--config`

### Examples

	lfsearch --action scan --search "my search string" --limit 10 --file /path/to/files

	lfsearch --action scan --search "my search string" --output /tmp/log.txt --file /path/to/files

	lfsearch --action fetch --engine mc --search "my search string"

	lfsearch --action exists --engine shm --search "my search string"

	lfsearch --action store --engine rds --search "my search string" --file /path/to/data

	lfsearch --action delete --engine mc --search "my search string"

	lfsearch --config /path/to/config.conf --search "my string"

## Prerequisite

* libmemcached >= 1.0.18
* libsasl2-dev >= libsasl2.so.2.0.25
* libhiredis >= 0.10

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

### redis

	sudo apt-get install libhiredis-dev

### LD_LIBRARY_PATH

if:

	echo $LD_LIBRARY_PATH

return nothing, then add the LD_LIBRARY_PATH to your ~/.bashrc. For example:

	export LD_LIBRARY_PATH=/usr/local/lib

## Build

To build run:

	make

This will create the main app:

	lfsearch

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

### Clear shared memory

	for x in `ipcs -m | grep "$USER" | cut -d' ' -f2`; do ipcrm shm $x; done;

## Config file

A Config file can be specified to allow parameters to be parse automatically. To see all available options please refer to the "Parameters" section.
