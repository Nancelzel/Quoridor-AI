CXX := g++
FLAGS :=
SOURCE := main.cpp Quoridor.cpp

all: main

main: *.cpp *.h
	${CXX} -o quoridor ${SOURCE} ${FLAGS} ${LIB}

clean: 
	rm quoridor
