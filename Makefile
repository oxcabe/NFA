CC=g++
FLAGS=-Wall -std=c++11
INCLUDE=include/
BIN=bin/nfa
SRC=src/
MAIN=main.cpp

all:
	$(CC) $(FLAGS) -o $(BIN) $(wildcard $(INCLUDE)* $(SRC)* $(MAIN))
