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

void printRfcolor(dirent *dirtp, struct stat s)
{
	std::cout<< std::endl;
	std::cout<< std::setw(2) << std::right << "."<<std::endl;
	std::cout<< ".."<< std::endl;
	//execute multiple line format with alphabatizing code
	
	return;
}
void printlfcolor(char * dirtp)
{
	struct stat s;
	if(S_ISDIR(s.st_mode) && dirtp[0] != '.')//
	{	
		printf("\033[0;34m");
		printf(dirtp);
		printf("\33[0m");
	}
	else if(S_ISDIR(s.st_mode) && dirtp[0] == '.')
	{	
		printf("\033[47m\033[38;5;34m");
		printf(dirtp);
		printf("\33[0m");
	}
	else if ((s.st_mode & S_IXUSR) && dirtp[0] != '.')//green
	{
		printf("\033[0;32m");
		printf(dirtp);
		printf("\33[0m");
	}
	else if ((s.st_mode & S_IXUSR) && dirtp[0] == '.')
	{
		printf("\033[47m\033[38;5;32m");
		printf(dirtp);
		printf("\33[0m");
	}
	else if(dirtp[0] == '.')//
	{
		printf("\033[0;47m");
		printf(dirtp);
		printf("\33[0m");
	}
	else//black
	{
		printf(dirtp);
	}
}

#endif
