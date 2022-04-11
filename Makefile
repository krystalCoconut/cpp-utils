CC = clang++
TARGET = linkedlisttest

all: 
	$(CC) -std=c++11 listTest.cpp -o $(TARGET)
run:
	./$(TARGET)
clean:
	rm $(TARGET)