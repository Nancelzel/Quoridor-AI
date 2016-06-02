CXX := g++
FLAGS := -std=c++11 -g
SOURCE := *.cpp

all: main

main: *.cpp *.h
	${CXX} -o quoridor ${SOURCE} ${FLAGS} ${LIB}

clean: 
	rm quoridor
