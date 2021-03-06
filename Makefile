SHELL = /bin/bash

BUFFERSIZE = 16777216

MAKE_JOBS_SAFE=	yes

CC = g++

CFLAGS = -O0 -pipe -Wall -I/usr/include/mysql -I/usr/include/mysql++ -Iinclude -DLWSYNC_HAS_NO_BOOST -DBUFFERSIZE=$(BUFFERSIZE)
LDFLAGS = -lv8 -llacewing -lmysqlclient -lmysqlpp
COMPILE = $(CC) $(CFLAGS) -c -pipe

OBJFILES := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

debug: b64 jsonpp stumpd

	$(CC) -o stumpd -g $(CFLAGS) main.cpp src/b64/*.o src/jsonpp/*.o src/stumpd/*.o $(LDFLAGS)


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
	$(MAKE) -C src/b64/ clean
	$(MAKE) -C src/stumpd/ clean
	rm -f stumpd
