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

void exitcode(char** k)
{
	char* h;
	int r = 0;
	for(int p = 0; k[p]; p++)
	{
		for(int q = 0; k[p][q]; q++)
		{
			h[r] = k[p][q];
			r++;
		}
		h[r] = '\0';
		if(strcmp(h, "exit") == 0)
		{
			exit(1);
		}
		r = 0;
	}
	return;
}


#endif 
