.POSIX:
.SUFFIXES:
CC=gcc

run: main
	./output/main

run-debug: debug
	gdb ./output/main


main: main.c
	mkdir -p output
	$(CC) main.c lib/*.c -l raylib -l m -Wall -o output/main

debug: main.c
	mkdir -p output
	$(CC) main.c lib/*.c -l raylib -l m -Wall -g -fsanitize=undefined -o output/main

clean:
	rm -f output/main

.PHONY: run clean
