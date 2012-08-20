# Makefile for biolib
# Corran C. Musk 2012-08-20
#
CC=gcc

biolib_sqlite3 : biolib_sqlite3.c
	$(CC) -shared -fPIC -Isqlite3 -o biolib_sqlite3 biolib_sqlite3.c

biolib.o : biolib.c
	$(CC) biolib.c
