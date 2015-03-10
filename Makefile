#ifndef MAKE
#define MAKE


sob = src/shell/main.cpp
lsob = src/ls/ls.cpp
pob = src/piping/main.cpp
objects = src/main.cpp

flags = -Wall -Werror -ansi -pedantic

all: rshell ls piping signal

rshell: $(objects)
	g++ $(flags) $(sob) -o shell.o
	mv shell.o bin/rshell

ls: $(objects)
	g++ $(flags) $(lsob) -o ls.o
	mv ls.o bin/ls

piping:$(objects)
	g++ $(flags) $(pob) -o pipe.o
	mv pipe.o bin/pipe

signal:$(objects)
	g++ $(flags) $(objects) -o signal.o
	mv signal.o bin/signal

clear:
	rm -mf bin

#endif
