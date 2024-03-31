# CS 370
# Simple make file for project #5A

CFLAGS	= -ggdb -O0 -pthread

duckNums:	duckNums.c
	gcc $(CFLAGS) -o duckNums duckNums.c

clean:
	@rm -f duckNums

