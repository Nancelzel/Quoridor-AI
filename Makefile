CXX := g++
FLAGS := -std=c++11
SOURCE := main.cpp Quoridor.cpp

all: main

main: *.cpp *.h
	${CXX} -o quoridor ${SOURCE} ${FLAGS} ${LIB}

clean: 
	rm quoridor
