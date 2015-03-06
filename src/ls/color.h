#ifndef COLOR_H
#define COLOR_H

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

using namespace std;

void printlfcolor(struct stat s, dirent * dirtp)
{
	if(s.st_mode & S_IFDIR) //blue
	{	
		if(dirtp->d_name[0] == '.')
		{
			printf("\033[47m\033[38;5;32m");
			printf(dirtp->d_name);
			printf("\033[0;00m");
		}
		else
		{
			printf("\033[38;5;32m");
			printf(dirtp->d_name);
			printf("\033[0;00m");
		}
	}
	else if ((s.st_mode & S_IXUSR))//green
	{
		if(dirtp->d_name[0] == '.')
		{
			printf("\033[47m\033[38;5;34m");
			printf(dirtp->d_name);
			printf("\033[0;00m");
		}
		else
		{
			printf("\033[38;5;34m");
			printf(dirtp->d_name);
			printf("\33[0;00m");
		}
	}
	else if(dirtp->d_name[0] == '.')//
	{
		printf("\033[0;47m");
		printf(dirtp->d_name);
		printf("\033[0;00m");
	}
	else//black
	{
		printf(dirtp->d_name);
	}
}

#endif
