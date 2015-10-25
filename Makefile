all: refstr

refstr: refstr.c refstr.h
	gcc refstr.c -o refstr


