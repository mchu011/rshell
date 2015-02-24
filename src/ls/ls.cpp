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
#include "date.h"
#include "flaga.h"
#include "flagl.h"
#include "flagR.h"
#include "getinfo.h"

using namespace std;


int main(int argc, char *argv[])
{
	if(argc < 1)
	{
		perror("please enter arguments");
		exit(1);
	}
	/*if(argv[1] != "ls")
	{
		perror("this is ls code, please use ls");
		exit(1);
	}*/

	char* dirName =(char*)".";		//this is to get current directory
	DIR* directory;
	directory = opendir(dirName);
	dirent *dirtpoint;
	vector<string> dirfiles;
				
	while((dirtpoint = readdir(directory)))
	{
		//std::cout<< dirtpoint->d_name << std::endl;
		if(errno != 0)
		{
			perror("there's a problem in read dir");
			exit(1);
		}
		dirfiles.push_back(dirtpoint->d_name);
	}

	sort(dirfiles.begin(), dirfiles.end(),locale("en_US.UTF-8"));

	if(closedir(directory) == -1)
	{
		perror("there's a problem in closedir");
		exit(1);
	}

	bool flagA = false;
	bool flagL = false;
	bool flagR = false;
	bool ignore = false;	
	
	int j;
	char* order[10];
	int loopcnt = 0;

	while(argv[loopcnt]) //if there are more than two commands to run
	{	
		j = 0;

		for(int i = 1; i < argc; i++)
		{
			if(argv[i][0] == '-')
			{
				for(unsigned int k = 1; k < sizeof(argv[i]);k++)
				{
					if(argv[i][k] == 'a')
					{
						flagA = true;
						order[j] = (char*)"flagA";
						j++;
					}
					if(argv[i][k] == 'l')
					{
						flagL = true;
						order[j] = (char*)"flagL";
						j++;
					}
					if(argv[i][k] == 'R')
					{
						flagR = true;
						order[j] = (char*)"flagR";
						j++;
					}
				}
			}
		}
		order[j] = '\0';


		for(int k = 0; order[k]; k++)
		{
			if(strcmp(order[k], "flagA") == 0)
			{
				if(flagA)
				{
					ignore = false;
					//s = takeoutdots(s,ignore);
					printa(dirfiles);
				}
			}
			if(strcmp(order[k], "flagL") == 0)
			{
				if(flagL)
				{
					ignore = true;
					//s = takeoutdots(s,ignore);
					printl(dirfiles);//execute case b
				}
			}
			if(strcmp(order[k], "flagR") == 0)
			{
				if(flagR)
				{
					printf(".:\n");
					ignore = true;
					//s = takeoutdots(s,ignore);
					printR(dirfiles);
				}
			}
		}

		if(!(flagA ||flagL ||flagR))
		{
			//printls(argv, dirtpoint); //not declared yet
			execvp(argv[0], argv);	
		}

		loopcnt++;
		if(argv[loopcnt] == NULL)
		{
			break;
		}
	}
	printf("\n");
	
	return 0;
}
