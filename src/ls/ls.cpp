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

#include "ignoredots.h"
//#include "colformat.h"
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

	char* dirName =(char*)".";		//this is to get current directory
	DIR* directory;
	directory = opendir(dirName);
	dirent *dirtpoint;
	vector<string> dirfiles;
				
	while((dirtpoint = readdir(directory)))
	{
		if(errno != 0)
		{
			perror("there's a problem in read dir");
			exit(1);
		}
		dirfiles.push_back(dirtpoint->d_name);//gets filename
	}

	sort(dirfiles.begin(), dirfiles.end(),locale("en_US.UTF-8"));//sorts files

	bool flagA = false;
	bool flagL = false;
	bool flagR = false;
	bool ignore = false;	
	
	int findmxsz;
	vector<string> store;

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
		//column format
		store = takeoutdots(dirfiles);
		//printcol(store);
		execvp(argv[1], argv);	
	}
	else if(flagA && flagL && flagR)//if alR, lRa, Ral, aRl,
	{			//laR, or Rla
		printf(".:\n");
		printl(dirfiles);
	}
	else if(flagA && flagL)	//if la or al
	{
		printl(dirfiles);
	}
	else if(flagA && flagR)	//if aR or Ra
	{
		printf(".:\n");
		//column format
		//printcol(dirfiles);
	}
	else if(flagL && flagR)	//if lR or Rl
	{
		printf(".:\n");
		store = takeoutdots(dirfiles);
		printl(store);
	}
	else if(flagA)	//if a
	{
		//column format
		//printcol(dirfiles);
	}	
	else if(flagL)	// if l
	{
		store = takeoutdots(dirfiles);
		printl(store);//execute
	}
	else if(flagR)	//if R
	{
		printf(".:\n");
		//column format
		store = takeoutdots(dirfiles);
		//printcol(store);
	}
	printf("\n");

	if(closedir(directory) == -1)
	{
		perror("there's a problem in closedir");
		exit(1);
	}
	
	return 0;
}
