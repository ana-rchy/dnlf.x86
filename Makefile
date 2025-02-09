.POSIX:
.SUFFIXES:
CC=gcc

run: main
	./output/main


main: main.c
	$(CC) main.c lib/*.c -l raylib -l m -Wall -o output/main

clean:
	rm -f output/main

.PHONY: run clean
