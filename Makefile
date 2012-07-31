SHELL = /bin/bash

BUFFERSIZE = 16777216

MAKE_JOBS_SAFE=	yes

CC = g++

CFLAGS = -g -O0 -Wall -I/usr/include/mysql -I/usr/include/mysql++ -Iinclude -DLWSYNC_HAS_NO_BOOST -DBUFFERSIZE=$(BUFFERSIZE)
LDFLAGS = -lv8 -llacewing -lmysqlclient -lmysqlpp

COMPILE = $(CC) $(CFLAGS) -c

OBJFILES := $(patsubst %.cpp,%.o,$(wildcard *.cpp))


all: b64 jsonpp stumpd


	$(CC) -o stumpd $(CFLAGS) main.cpp src/b64/*.o src/jsonpp/*.o src/stumpd/*.o $(LDFLAGS)


b64:

	$(MAKE) -C src/b64


jsonpp:

	$(MAKE) -C src/jsonpp


stumpd:

	$(MAKE) -C src/stumpd



#%.o: %.cpp
#
#	$(COMPILE) -o $@ $<



clean :

	$(MAKE) -C src/jsonpp/ clean
	$(MAKE) -C src/stumpd/ clean
	rm -f stumpd
