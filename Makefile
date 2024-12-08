TARGET = LINUX

CC_LINUX = gcc
CC_MINGW = x86_64-w64-mingw32-gcc
CC = $(CC_LINUX)


CFLAGS = -Wall -Wextra -std=c99 -O2 -pipe

LDFLAGS_MINGW = -L./lib -lraylib -lopengl32 -lgdi32 -lwinmm
LDFLAGS_LINUX = -L./lib -lraylib -ldl -pthread -lm
LDFLAGS = $(LDFLAGS_LINUX)

INCLUDE = -I./raylib
BUILD = ./build
NAME = snakec
FPATH = $(BUILD)/$(NAME)

RAYLIB_TARGET_LINUX = PLATFORM=PLATFORM_DESKTOP
RAYLIB_TARGET_MINGW = PLATFORM=PLATFORM_DESKTOP PLATFORM_OS=WINDOWS RAYLIB_LIBTYPE=SHARED
RAYLIB_TARGET = $(RAYLIB_TARGET_LINUX)


ifeq ($(TARGET),MINGW)
	CC = $(CC_MINGW)
	LDFLAGS = $(LDFLAGS_MINGW)
	RAYLIB_TARGET = $(RAYLIB_TARGET_MINGW)
	FPATH = $(BUILD)/$(NAME).exe
endif

buildp:
	if ! [ -d $(BUILD) ]; then \
		mkdir $(BUILD); \
	fi

engine:
	make -C raylib CC=$(CC) $(RAYLIB_TARGET)
	if ! [ -d lib ]; then \
		mkdir lib; \
	fi

	if ! [ -d include ]; then \
		mkdir include; \
	fi

	if [[ $(TARGET) == "MINGW" ]]; then \
		mv src/libraylibdll.a src/raylib.dll -t lib; \
	else \
		mv src/libraylib.a lib; \
	fi

	cp raylib/raylib.h raylib/raymath.h raylib/rlgl.h -t include

game.o: src/game.h src/game.c
	$(CC) $(CFLAGS) -c src/game.h src/game.c $(INCLUDE) $(LDFLAGS)

snake.o: src/snake.h src/snake.c
	$(CC) $(CFLAGS) -c src/snake.h src/snake.c $(INCLUDE) $(LDFLAGS)

all: game.o snake.o src/main.c
	make engine
	make buildp

	$(CC) $(CFLAGS) -o $(FPATH) snake.o game.o $(INCLUDE) src/main.c $(LDFLAGS)

	if [[ $(TARGET) == "MINGW" ]]; then \
		cp -u lib/raylib.dll build; \
	fi

other: snake_example.c
	make engine
	make buildp
	$(CC) $(CFLAGS) -o $(BUILD)/snake_ex $(INCLUDE) snake_example.c $(LDFLAGS)

clean:
	rm -rv *.o
	rm src/game.h.gch
	rm src/snake.h.gch
	rm -rv build
	rm -rv include lib
	make -C raylib clean

.DEFAULT_GOAL := all
