#ifndef	GETINFO_H
#define	GETINFO_H

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


/*void printlinfo(struct stat s)
{
	struct passwd* pw;
	struct group* grp;

	if(!((pw = getpwuid(s.st_uid)) != '\0'))
	{
		perror("There's an error at getpwuid");
		exit(1);
	}

	if(!((grp = getgrgid(s.st_gid)) != '\0'))
	{
		perror("There's an error at getgrid");
		exit(1);
	}

	std::cout << pw-> pw_name << " ";
	std::cout << grp->gr_name << " ";
}*/
	
void assigninfo(struct stat s, char*& u, char h[])
{	
	if(getpwuid(s.st_uid)) 
	{
		perror("there's an error in getpwuid");
		exit(1);
	}

	if(getlogin() == NULL)				//get username
	{
		perror("No username");
		char* name = (char*)"unknownUser";
		u = name;
	}
	else
	{
		u = getlogin();
	}
	
	if(-1 == gethostname(h, 50))		//get hostname
	{
		perror("There's a problem in gethostname");
		exit(1);
	}
	return;
}


#endif
