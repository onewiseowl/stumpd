CC = g++

CFLAGS = -g -pipe -c -O0 -Wall -I../../include/

COMPILE = $(CC) $(CFLAGS) -c



all : json_reader.o json_value.o json_writer.o


json_reader.o :

	$(CC) $(CFLAGS) json_reader.cpp


json_value.o :

	$(CC) $(CFLAGS) json_value.cpp


json_writer.o :

	$(CC) $(CFLAGS) json_writer.cpp


clean :

	rm -f *.o

