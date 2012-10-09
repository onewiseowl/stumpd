SHELL = /bin/bash

BUFFERSIZE = 16777216

CC = g++

CFLAGS = -g -pipe -O0 -Wall -I../../include -DBUFFERSIZE=$(BUFFERSIZE)

COMPILE = $(CC) $(CFLAGS) -c

OBJFILES := $(patsubst %.cpp,%.o,$(wildcard *.cpp))


base64.o : 

	$(COMPILE) base64.cpp

clean :

	rm -f *.o *.a

