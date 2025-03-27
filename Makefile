.POSIX:
.SUFFIXES:
CC=gcc
WCC=x86_64-w64-mingw32-gcc
BUILD_FLAGS=-l raylib -l m -l GL -l pthread -l dl -l rt -l X11 -Wall

run: output/DNLF.x86
	./output/DNLF.x86

run-debug: output/DNLF.x86.debug
	gdb ./output/DNLF.x86.debug

run-win: output/DNLF.x86.exe
	./output/DNLF.x86.exe


build output/DNLF.x86: main.c lib/ lib/payloads/
	mkdir -p output
	$(CC) main.c lib/*.c lib/payloads/*.c $(BUILD_FLAGS) -o output/DNLF.x86

build-debug output/DNLF.x86.debug: main.c lib/ lib/payloads/
	mkdir -p output
	$(CC) main.c lib/*.c lib/payloads/*.c $(BUILD_FLAGS) -g -fsanitize=undefined -o output/DNLF.x86

build-win output/DNLF.x86.exe: main.c lib/ lib/payloads/ lib/raylib/src/libraylib.a
	mkdir -p output
	$(WCC) main.c lib/*.c lib/payloads/*.c -I 'lib/raylib/src/' 'lib/raylib/src/libraylib.a' -l m -l gdi32 -l winmm -g -o output/DNLF.x86.exe	


raylib-win lib/raylib/src/libraylib.a: lib/raylib/src/
	cd lib/raylib/src; \
	make clean; \
	make OS=Windows_NT CC=x86_64-w64-mingw32-gcc AR=x86_64-w64-mingw32-ar


clean:
	rm -f output/DNLF.x86
	rm -f output/DNLF.x86.exe
	rm -f .howtoplay
	rm -f .glitchpass

.PHONY: run run-debug run-win build build-debug build-win clean
