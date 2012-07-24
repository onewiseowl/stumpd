SHELL = /bin/bash

CC = g++

CFLAGS = -g -O0 -Wall -I/usr/include/mysql -I/usr/include/mysql++ -Iinclude -lv8 -llacewing -lmysqlclient -lmysqlpp -DLWSYNC_HAS_NO_BOOST

COMPILE = $(CC) $(CFLAGS) -c

OBJFILES := $(patsubst %.cpp,%.o,$(wildcard *.cpp))


all: jsonpp stumpd

	$(CC) -o stumpd $(CFLAGS) main.cpp src/jsonpp/*.o src/stumpd/*.o


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
