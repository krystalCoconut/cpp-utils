CC = clang++
TARGET = octTreeTest
DEBUG = -g

all: space.o
	$(CC) $(DEBUG) -std=c++11 octTreeTest.cpp Space/space.o -o $(TARGET)
space.o:
	cd Space && $(MAKE)
run:
	./$(TARGET)
clean:
	rm Space/space.o
	rm $(TARGET)
