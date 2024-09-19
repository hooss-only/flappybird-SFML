CC=g++
FLAGS=-Wall -g
LIB_FLAGS=-lsfml-graphics -lsfml-window -lsfml-system

TARGET=./build/output/flappybird

output: main.o sprite.o scene.o
	$(CC) -o $(TARGET) ./build/*.o $(FLAGS) $(LIB_FLAGS)

main.o:
	$(CC) -o ./build/main.o ./src/main.cpp -c

sprite.o:
	$(CC) -o ./build/sprite.o ./src/objects/sprite.cpp -c

scene.o:
	$(CC) -o ./build/scene.o ./src/objects/scene.cpp -c
