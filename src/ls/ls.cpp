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


int main(int argc, char *argv[])
{
	if(argc < 1)
	{
		perror("please enter arguments");
		exit(1);
	}
	if(strcmp(argv[1],"ls") != 0) //checks if variables are ls
	{
		perror("this is ls code, please use ls");
		exit(1);
	}

	bool flagA = false;
	bool flagL = false;
	bool flagR = false;
	bool ignore = false;	
	
	for(int i = 2; i < argc; i++)	//check for flags
	{
		if(argv[i][0] == '-')
		{
			for(unsigned int k = 1; k < sizeof(argv[i]);k++)
			{
				if(argv[i][k] == 'a')
				{
					flagA = true;
				}
				if(argv[i][k] == 'l')
				{
					flagL = true;
				}
				if(argv[i][k] == 'R')
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
		execvp(argv[1], argv);	
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
	
	return 0;
}
