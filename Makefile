# Makefile for biolib
# Corran C. Musk 2012-08-20
#
CC=gcc
SQLITE_OBJS= biolib.o biolib_sqlite3.o
TESTPROG_OBJS= biolib.o biolib_test.o

all : biolib_sqlite3 biolib.o biolib_test

test : biolib_sqlite3
	sqlite3 < test.sqlite

biolib_test : $(TESTPROG_OBJS)
	$(CC) -o biolib_test $(TESTPROG_OBJS)

biolib_test.o : biolib_test.c
	$(CC) -o biolib_test.o -c biolib_test.c

biolib_sqlite3 : $(SQLITE_OBJS)
	$(CC) -shared -fPIC -o biolib_sqlite3 $(SQLITE_OBJS)

biolib_sqlite3.o : biolib_sqlite3.c
	$(CC) -shared -fPIC -Isqlite3 -c biolib_sqlite3.c

biolib.o : biolib.c biolib.h
	$(CC) -fPIC -c biolib.c

clean :
	rm -f biolib_sqlite3 *.o

tidy :
	rm -f *.o

