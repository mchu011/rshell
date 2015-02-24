#ifndef EXECUTE_H
#define EXECUTE_H

#include <unistd.h>
#include <stdio.h>

#include "cntexec.h"

void myexec(char** a)
{
	for(int i = 0; a[i]; i++)
	{
		if(a[i] == ";" || a[i] == "&&" || a[i] == "||")
		{
			cnctexec(a);
		}
	}
	
	if(execvp(a[0],a) == -1)
	{
		perror("myexec execvp");
		exit(1);
	}
	
	return;
}

#endif
