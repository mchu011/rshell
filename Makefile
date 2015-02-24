#ifndef MAKE
#define MAKE

objects = src/main.cpp

flags = -Wall -Werror -ansi -pedantic

all: rshell cp ls piping
	mv all bin

rshell: $(objects)
	g++ $(flags) $(objects) -o rshell.o

cp: $(objects)
	g++ $(flags) $(objects) -o cp.o

ls: $(objects)
	g++ $(flags) $(objects) -o ls.o

piping:$(objects)
	g++ $(flags) $(objects) -o pipe.o

clear:
	rm -mf bin

#endif
