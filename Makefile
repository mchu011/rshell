#ifndef MAKE
#define MAKE

objects = src/main.cpp

flags = -Wall -Werror -ansi -pedantic

all: rshell ls piping signal
	mv all bin

rshell: $(objects)
	g++ $(flags) $(objects) -o shell.o

ls: $(objects)
	g++ $(flags) $(objects) -o ls.o

piping:$(objects)
	g++ $(flags) $(objects) -o pipe.o

signal:$(objects)
	g++ $(flags) $(objects) -o signal.o

clear:
	rm -mf bin

#endif
