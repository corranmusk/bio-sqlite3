***********************************
* BioLib - Bioinformatics library *
*                                 *
* Corran C Musk 2012              *
***********************************
Biolib is a library written in C to provide useful function for use in bioinformatics.

bio-sqlite3 is an extension to the library for sqlite3 that allows the functions to be used there. Primarily it is a proof of concept, let's be honest sqlite3 is not the best candidate for this, but it seems a sensible idea to add such functions to databases that will be used for storing sequences anyway and to get it to do the work. Next step MySQL.

Required packages:
	sqlite3
	libsqlite3-dev (to make the library)
	
Installation:
	make 		(will make the library)
	make test	(runs a test sqlite3 script)
	
Usage:
	Having compiled the library as above start sqlite3
	Enter the command: .load biolib_sqlite3
	This will load the library and allow execution of the commands listed in FUNCTIONS.txt
	See test.sqlite for an example.

Files:
	README.md	This file, duh!
	INSTALL.txt	How to make and use the library
	FUNCTIONS.txt	List of functions currently provided
	Makefile	Makefile to make the library
	biolib.c (.h)	The base library containing the functions
	biolib_sqlite3.c	Allows the functions to be used in sqlite3	
	words.db	A sqlite database containing some words for testing
	seqtest.db	A sqlite database containing some sequences for testing
	test.sqlite	A testing script
