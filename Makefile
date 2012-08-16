biolib : biolib.c
	gcc -shared -fPIC -Isqlite3 -o biolib biolib.c
