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
EXPATH = $(BUILD)/snake_ex

RAYLIB_TARGET_LINUX = PLATFORM=PLATFORM_DESKTOP
RAYLIB_TARGET_MINGW = PLATFORM=PLATFORM_DESKTOP PLATFORM_OS=WINDOWS RAYLIB_LIBTYPE=SHARED
RAYLIB_TARGET = $(RAYLIB_TARGET_LINUX)


ifeq ($(TARGET),MINGW)
	CC = $(CC_MINGW)
	LDFLAGS = $(LDFLAGS_MINGW)
	RAYLIB_TARGET = $(RAYLIB_TARGET_MINGW)
	FPATH = $(BUILD)/$(NAME).exe
	EXPATH = $(BUILD)/snake.exe
endif

.PHONY: buildp
buildp:
	if ! [ -d $(BUILD) ]; then \
		mkdir $(BUILD); \
	fi

	if ! [ -d obj ]; then \
		mkdir obj; \
	fi

	if [[ $(TARGET) == "MINGW" ]]; then \
		cp -u lib/raylib.dll build; \
	fi

.PHONY: engine
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

obj/%.o: $(wildcard src/*.c src/*.h)
	$(CC) $(CFLAGS) -c $^ $(INCLUDE) $(LDFLAGS)
	mv $(wildcard *.o) -t obj

OBJECTS = obj/game.o \
      obj/snake.o \
      obj/food.o

all: $(OBJECTS) src/main.c
	make engine
	make buildp

	$(CC) $(CFLAGS) -o $(FPATH) $(OBJECTS) $(INCLUDE) src/main.c $(LDFLAGS)

.PHONY: other
other: snake_example.c
	make engine
	make buildp
	$(CC) $(CFLAGS) -o $(EXPATH) $(INCLUDE) snake_example.c $(LDFLAGS)

.PHONY: clean
clean:
	rm -rv $(OBJECTS)
	rm src/game.h.gch
	rm src/snake.h.gch
	rm src/food.h.gch
	rm -rv build
	rm -rv obj
	rm -rv include lib
	make -C raylib clean

.DEFAULT_GOAL := all

.PRECIOUS := %.o Makefile
