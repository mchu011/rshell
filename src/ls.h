#ifndef LS_H
#define LS_H

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <iomanip>
#include <time.h>
#include <ios>
#include <dirent.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <errno.h>

#include "color.h"
#include "ignoredots.h"
#include "colformat.h"
#include "listformat.h"

using namespace std;

void lscode(char** arg)
{
	bool flagA = false;
	bool flagL = false;
	bool flagR = false;
	bool ignore = false;	
	
	int sz = 0;
	for(;arg[sz]; sz++) {}

	for(int i = 1; i < sz; i++)	//check for flags
	{
		if(arg[i][0] == '-')
		{
			for(unsigned int k = 1; k < sizeof(arg[i]);k++)
			{
				if(arg[i][k] == 'a')
				{
					flagA = true;
				}
				if(arg[i][k] == 'l')
				{
					flagL = true;
				}
				if(arg[i][k] == 'R')
				{
					flagR = true;
				}
			}
		}
	}


	if(!(flagA ||flagL ||flagR))//if none of these flags
	{	
		//column formati
		ignore = true;
		//store = takeoutdots(dirfiles);
		//printcol(ignore);
		execvp(arg[1], arg);	
	}
	else if(flagA && flagL && flagR)//if alR, lRa, Ral, aRl,
	{			//laR, or Rla
		ignore = false;
		printf(".:\n");
		printl(ignore);
	}
	else if(flagA && flagL)	//if la or al
	{
		ignore = false;
		printl(ignore);
	}
	else if(flagA && flagR)	//if aR or Ra
	{
		ignore = false;
		printf(".:\n");
		//column format
		printcol(ignore);
	}
	else if(flagL && flagR)	//if lR or Rl
	{
		printf(".:\n");
		ignore = true;
		//store = takeoutdots(dirfiles);
		printl(ignore);
	}
	else if(flagA)	//if a
	{
		ignore = false;
		//column format
		printcol(ignore);
	}	
	else if(flagL)	// if l
	{
		ignore = true;
		//store = takeoutdots(dirfiles);
		printl(ignore);//execute
	}
	else if(flagR)	//if R
	{
		printf(".:\n");
		//column format
		ignore = true;
		//store = takeoutdots(dirfiles);
		printcol(ignore);
	}
	printf("\n");

	return;	
}

#endif
