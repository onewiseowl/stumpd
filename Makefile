SHELL = /bin/bash

BUFFERSIZE = 16777216

CC = g++

CFLAGS = -g -O0 -Wall -I/usr/include/mysql -I/usr/include/mysql++ -Iinclude -lv8 -llacewing -lmysqlclient -lmysqlpp -DLWSYNC_HAS_NO_BOOST -DBUFFERSIZE=$(BUFFERSIZE) -DENABLE_DEBUGGER_SUPPORT

COMPILE = $(CC) $(CFLAGS) -c

OBJFILES := $(patsubst %.cpp,%.o,$(wildcard *.cpp))


all: b64 jsonpp stumpd


	$(CC) -o stumpd $(CFLAGS) main.cpp src/b64/*.o src/jsonpp/*.o src/stumpd/*.o


b64:

	$(MAKE) -C src/b64


jsonpp:

	$(MAKE) -C src/jsonpp


stumpd:

	$(MAKE) -C src/stumpd



%.o: %.cpp

	$(COMPILE) -o $@ $<



clean :

	$(MAKE) -C src/jsonpp/ clean
	$(MAKE) -C src/stumpd/ clean
	rm -f stumpd
