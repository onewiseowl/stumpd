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
all : htpasswd_auth_source.o authentication_session.o authentication.o api.o api_addFilter.o api_auth.o api_getFilters.o api_getHosts.o api_getInputs.o api_getTriggers.o api_insert.o api_search.o api_testScript.o api_updateFilter.o dotcom.o page_method.o filters.o global_fs.o insert.o load_config.o search.o set_cli_opts.o sighandler.o udp_server.o base64.o is_file.o split.o v8.o

htpasswd_auth_source.o:

	$(CC) $(CFLAGS) authentication/htpasswd_auth_source.cpp


authentication_session.o:

	$(CC) $(CFLAGS) authentication/authentication_session.cpp


authentication.o:

	$(CC) $(CFLAGS) authentication/authentication.cpp


api.o:

	$(CC) $(CFLAGS) dotcom/api.cpp


api_addFilter.o:

	$(CC) $(CFLAGS) dotcom/api_addFilter.cpp


api_auth.o:

	$(CC) $(CFLAGS) dotcom/api_auth.cpp


api_getFilters.o:

	$(CC) $(CFLAGS) dotcom/api_getFilters.cpp


api_getHosts.o:

	$(CC) $(CFLAGS) dotcom/api_getHosts.cpp


api_getInputs.o:

	$(CC) $(CFLAGS) dotcom/api_getInputs.cpp


api_getTriggers.o:

	$(CC) $(CFLAGS) dotcom/api_getTriggers.cpp


api_insert.o:

	$(CC) $(CFLAGS) dotcom/api_insert.cpp


api_search.o:

	$(CC) $(CFLAGS) dotcom/api_search.cpp


api_testScript.o:

	$(CC) $(CFLAGS) dotcom/api_testScript.cpp


api_updateFilter.o:

	$(CC) $(CFLAGS) dotcom/api_updateFilter.cpp


dotcom.o:

	$(CC) $(CFLAGS) dotcom/dotcom.cpp


page_method.o:

	$(CC) $(CFLAGS) dotcom/page_method.cpp


filters.o:

	$(CC) $(CFLAGS) filters.cpp


global_fs.o:

	$(CC) $(CFLAGS) global_fs/global_fs.cpp


insert.o:

	$(CC) $(CFLAGS) insert.cpp


load_config.o:

	$(CC) $(CFLAGS) load_config.cpp


search.o:

	$(CC) $(CFLAGS) search.cpp


set_cli_opts.o:

	$(CC) $(CFLAGS) set_cli_opts.cpp


sighandler.o:

	$(CC) $(CFLAGS) sighandler.cpp


udp_server.o:

	$(CC) $(CFLAGS) udp_server.cpp


base64.o:

	$(CC) $(CFLAGS) utilities/base64.cpp


is_file.o:

	$(CC) $(CFLAGS) utilities/is_file.cpp


split.o:

	$(CC) $(CFLAGS) utilities/split.cpp


v8.o:

	$(CC) $(CFLAGS) v8/v8.cpp


clean :

	rm -f *.o
