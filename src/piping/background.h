#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>

using namespace std;

bool bgd(int p, char** cmds)
{
	bool backgck = false;
	if(p > 0) p--;	//sets to last cmd
	
	if(strcmp(cmds[p], "&") == 0)//checks if last
	{				//cmd is &
		backgck = true;
		cmds[p] = NULL;
	}
	else
	{
		char* cker = cmds[p];
		int clen = strlen(cmds[p]) -1;
		if(cker[clen] == '&')//checks if last
		{		//parse ends with '&'
			backgrdck = true;
			cker[clen] = '\0';
			cmds[p] = cker;
		}
	}
		
	return backgck;//returns true/false
}
	

#endif
