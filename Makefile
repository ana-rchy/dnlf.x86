.POSIX:
.SUFFIXES:
CC=gcc
WCC=x86_64-w64-mingw32-gcc
BUILD_FLAGS=-l raylib -l m -l GL -l pthread -l dl -l rt -l X11 -Wall

run: main
	./output/main

run-debug: debug
	gdb ./output/main


main: main.c
	mkdir -p output
	$(CC) main.c lib/*.c $(BUILD_FLAGS) -o output/main

debug: main.c
	mkdir -p output
	$(CC) main.c lib/*.c $(BUILD_FLAGS) -g -fsanitize=undefined -o output/main


raylib: lib/raylib/src/libraylib.a
	cd lib/raylib/src; \
	make clean; \
	make OS=Windows_NT CC=x86_64-w64-mingw32-gcc AR=x86_64-w64-mingw32-ar

windows: main.c raylib
	mkdir -p output
	$(WCC) main.c lib/*.c -I 'lib/raylib/src/' 'lib/raylib/src/libraylib.a' -l m -l gdi32 -l winmm -g -o output/main.exe


clean:
	rm -f output/main
	rm -f output/main.exe

.PHONY: run run-debug clean
