.POSIX:
.SUFFIXES:

CC=gcc

run: main
	./main

main: main.c
	$(CC) main.c -I include -L lib -lraylib -lm -o main

clean:
	rm -f main

.PHONY: run clean
