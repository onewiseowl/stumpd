SHELL = /bin/bash

CC = g++

MAKE_JOBS_SAFE=	yes

BUFFERSIZE = 16777216

#CFLAGS = -g -c -O0 -Wall -I../../include/ -DLWSYNC_HAS_NO_BOOST -I/usr/include/mysql -I/usr/include/mysql++ -Iinclude -lv8 -llacewing -lmysqlclient -lmysqlpp -DBUFFERSIZE=$(BUFFERSIZE) -DENABLE_DEBUGGER_SUPPORT

ifeq ($(DEBUG),true)
CFLAGS=+-g
endif

CFLAGS = -g -pipe -c -Wall -I../../include/ -I/usr/include/mysql -I/usr/include/mysql++ -Iinclude -DLWSYNC_HAS_NO_BOOST -DBUFFERSIZE=$(BUFFERSIZE)
LDFLAGS= -lv8 -llacewing -lmysqlclient -lmysqlpp

COMPILE = $(CC) $(CFLAGS) -c


#all : utilities.o global_fs.o authentication.o v8.o dotcom.o
all : utilities.o global_fs.o authentication.o v8.o dotcom.o assorted.o


assorted.o :
	$(CC) $(CFLAGS) ./*.cpp


utilities.o :

	$(CC) $(CFLAGS) utilities/*.cpp 


global_fs.o :

	$(CC) $(CFLAGS) global_fs/*.cpp


authentication.o :

	$(CC) $(CFLAGS) authentication/*.cpp


dotcom.o :

	$(CC) $(CFLAGS) dotcom/*.cpp


v8.o :

	$(CC) $(CFLAGS) v8/*.cpp


clean :

	rm -f *.o
