.PHONY: directories clean
CC=g++
CFLAGS=-std=c++11
LIBS=-lgtest -lpthread
OBJ=obj
BIN=bin
SRC=src
TEST=test

all: directories main.cpp

main.cpp: $(SRC)/scheduler.h $(SRC)/task.h $(SRC)/iterator.h $(SRC)/queue.h $(SRC)/timer.h
	$(CC) $(CFLAGS) -c $< -o $@

directories:
	mkdir -p bin obj

clean:
	rm -rf $(OBJ) $(BIN)

stat:
	wc $(SRC)/*.h $(SRC)/*.cpp $(TEST)/*.h $(TEST)/*.cpp
