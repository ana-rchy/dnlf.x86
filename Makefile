.POSIX:
.SUFFIXES:
CC=gcc
WCC=x86_64-w64-mingw32-gcc
BUILD_FLAGS=-l raylib -l m -l GL -l pthread -l dl -l rt -l X11 -Wall

run: main
	./output/DNLF.x86

run-debug: debug
	gdb ./output/DNLF.x86


main: main.c
	mkdir -p output
	$(CC) main.c lib/*.c lib/payloads/*.c $(BUILD_FLAGS) -o output/DNLF.x86

debug: main.c
	mkdir -p output
	$(CC) main.c lib/*.c lib/payloads/*.c $(BUILD_FLAGS) -g -fsanitize=undefined -o output/DNLF.x86


raylib: lib/raylib/src/libraylib.a
	cd lib/raylib/src; \
	make clean; \
	make OS=Windows_NT CC=x86_64-w64-mingw32-gcc AR=x86_64-w64-mingw32-ar

windows: main.c raylib
	mkdir -p output
	$(WCC) main.c lib/*.c lib/payloads/*.c -I 'lib/raylib/src/' 'lib/raylib/src/libraylib.a' -l m -l gdi32 -l winmm -g -o output/DNLF.x86.exe


clean:
	rm -f output/DNLF.x86
	rm -f output/DNLF.x86.exe
	rm -f .howtoplay
	rm -f .glitchpass

.PHONY: run run-debug clean
