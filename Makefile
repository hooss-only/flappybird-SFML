CC=clang++
FLAGS=-Wall -g
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system

BIN=bin
TARGET=$(BIN)/flappybird

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
	$(CC) -o $(TARGET) $(filter %.o,$^) $(FLAGS) $(LDFLAGS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(FLAGS)

clean:
	rm -rf $(BIN) $(OBJ)
