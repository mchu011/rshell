#ifndef MAKEFILE
#define MAKEFILE

objects = src/main.cpp

CFLAGS = -Wall -Werror -ansi -pedantic

all: rshell cp ls piping
	mv all bin
	
rshell: $(objects)
	g++ $(CFLAGS) $(objects) -o rshell.o

cp:
	g++ $(CFLAGS) $(objects) -o cp.o

ls:
	g++ $(CFLAGS) $(objects) -o ls.o

piping:
	g++ $(CFLAGS) $(objects) -o pipe.o

clean:
	rm -rf bin
	
#endif
