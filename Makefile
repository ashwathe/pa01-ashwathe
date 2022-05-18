# Makefile

all: game tests

game : main.cpp cards.cpp cards.h
	g++ -o game main.cpp cards.cpp

tests : cards.cpp tests.cpp tests.h
	g++ -o tests cards.cpp tests.cpp

clean :
	rm game tests