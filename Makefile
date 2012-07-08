SHELL = /bin/bash

CC = g++

CFLAGS = -g -O0 -Wall -I/usr/include/mysql -I/usr/include/mysql++ -Iinclude -llacewing -lmysqlclient -lmysqlpp -DLWSYNC_HAS_NO_BOOST

COMPILE = $(CC) $(CFLAGS) -c

OBJFILES := $(patsubst %.cpp,%.o,$(wildcard *.cpp))


all: jsonpp stumpd

	$(CC) -o stumpd $(CFLAGS) main.cpp src/jsonpp/*.o src/stumpd/*.o


jsonpp:

	cd src/jsonpp ; $(MAKE)


stumpd:

	cd src/stumpd ; $(MAKE)


%.o: %.cpp

	$(COMPILE) -o $@ $<



clean :

	rm -f stumpd
	pushd src/jsonpp ; make clean ; popd
	pushd src/stumpd ; make clean ;	popd
