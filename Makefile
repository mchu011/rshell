#ifndef MAKEFILE
#define MAKEFILE

objects = main.cpp

CFLAGS = -Wall -Werror -ansi -pedantic

all: rshell
	cd rshell bin
	
rshell: $(objects)
	g++ $(CFLAGS) $(objects)

clean:
	rm -rf rshell
	
#endif
