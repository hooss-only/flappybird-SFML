CC=clang++
CC_WIN=x86_64-w64-mingw32-c++
FLAGS=-Wall -g
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

BIN=bin
TARGET=$(BIN)/flappybird

PLATFORM ?= linux

SRC=$(shell find src -name '*.cpp')
OBJ=$(SRC:.cpp=.o)

all: dirs res build

run: build
	$(TARGET)

dirs:
	mkdir $(BIN) -p

res:
	cp Resources $(BIN)/ -r

build: dirs res $(OBJ)
ifeq ($(PLATFORM), linux)
	$(CC) -o $(TARGET) $(filter %.o,$^) $(FLAGS) $(LDFLAGS)
else ifeq ($(PLATFORM), windows)
	$(CC_WIN) -o $(TARGET).exe $(filter %.o,$^) -Llib/SFML-2.6.1/lib $(FLAGS) $(LDFLAGS) -lws2_32 -static -static-libgcc -static-libstdc++
endif

%.o: %.cpp
ifeq ($(PLATFORM), linux)
	$(CC) -o $@ -c $< $(FLAGS)
else ifeq($(PLATFORM), windows)
	$(CC_WIN) -o $@ -c $< $(FLAGS) -Ilib/SFML-2.6.1/include/
endif

clean:
	rm -rf $(BIN) $(OBJ)
