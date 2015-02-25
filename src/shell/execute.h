#ifndef EXECUTE_H
#define EXECUTE_H

#include <unistd.h>	//looks through tokens list
#include <stdio.h>	//for some reason, it skips the connectors

#include "cntexec.h"
#include "exit.h"

void myexec(char** a)
{
	bool complete = false;
	for(int i = 0; a[i]; i++)	//glances through token list
	{
		if(a[i] == ";" || a[i] == "&&" || a[i] == "||")//finds connector call
		{
			cnctexec(a);	//execute by connectors
			complete = true;
		}
	}

	if(complete == false) //execute if there are no connectors
	{
		if(execvp(a[0],a) == -1)
		{
			perror("myexec execvp");
			exit(1);
		}
	}
	
	return;
}

#endif
