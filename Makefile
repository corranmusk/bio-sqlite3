# Makefile for biolib
# Corran C. Musk 2012-08-20
#
CC=gcc
SQLITE_OBJS= biolib.o biolib_sqlite3.o

all : biolib_sqlite3 biolib.o

biolib_sqlite3 : $(SQLITE_OBJS)
	$(CC) -shared -o biolib_sqlite3 $(SQLITE_OBJS)

biolib_sqlite3.o : biolib_sqlite3.c
	$(CC) -shared -fPIC -Isqlite3 -c biolib_sqlite3.c

biolib.o : biolib.c
	$(CC) -c biolib.c

clean :
	rm -f biolib_sqlite3 *.o

tidy :
	rm -f *.o

