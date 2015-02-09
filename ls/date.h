#ifndef DATE_H
#define DATE_H

#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>

void printdate(struct stat s)
{
	time_t comptim= s.st_mtime;
	struct tm t;
	
	if(localtime_r(&comptim, &t) == '\0')
	{
		perror("There's a problem with localtime");
	}

	char timout[50];

	strftime(timout, 50, "%h", &t);
	std::cout << timout << " ";	
	
	strftime(timout, 50, "%d", &t);
	std::cout << timout << " ";	

	strftime(timout, 50, "%R", &t);
	std::cout << timout << " ";	
	return;
}

#endif
