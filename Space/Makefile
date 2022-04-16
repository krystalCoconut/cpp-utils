CC = clang++
TARGET = octTreeTest

all: space.o
	$(CC) -std=c++11 octTreeTest.cpp space.o -o $(TARGET)
space.o:
	$(CC) -std=c++11 space.cpp -c
run:
	./$(TARGET)
clean:
	rm space.o
	rm $(TARGET)
	