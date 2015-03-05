#ifndef EXIT_H
#define EXIT_H

#include <stdio.h>		//code for exit command
#include <unistd.h>
#include <string.h>

using namespace std;

void exitcode(char* k)
{
	if(strcmp(k, "exit") == 0)
	{
		exit(1);
	}
	return;
}

#endif 
