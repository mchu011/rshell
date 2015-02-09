#ifndef FLAGL_H
#define FLAGL_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <iomanip>
#include <ios>
#include <dirent.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>

#include "date.h"
#include "color.h"
using namespace std;

void printPermissions()
{
	struct stat s;
	if(s.st_mode & S_IFDIR)
	{
		std::cout << "d";
	}
	else if(!(s.st_mode & S_IFLNK))
	{
		std::cout << "l";
	}
	else
	{
		std::cout << "-";
	}
	printf((s.st_mode & S_IRUSR) ? "r" : "-");
	printf((s.st_mode & S_IWUSR) ? "w" : "-");
	printf((s.st_mode & S_IXUSR) ? "x" : "-");
	printf((s.st_mode & S_IRGRP) ? "r" : "-");
	printf((s.st_mode & S_IWGRP) ? "w" : "-");
	printf((s.st_mode & S_IXGRP) ? "x" : "-");
	printf((s.st_mode & S_IROTH) ? "r" : "-");
	printf((s.st_mode & S_IWOTH) ? "w" : "-");
	printf((s.st_mode & S_IXOTH) ? "x" : "-");

	std::cout << " "<< s.st_nlink << " ";
	return;
}

void printlinfo()		//error in this by pw_name and gr_name
{
	struct passwd *pw;
	struct group *grp;
	string uid, gid;
	struct stat s;

	if( !(pw = getpwuid(s.st_uid)))
	{
		perror("There's an error at getpwuid");
		exit(1);
	}
	else
	{
		uid = pw->pw_name;
		std::cout << uid << " ";
	}

	if(!(grp = getgrgid(s.st_gid)))
	{
		perror("There's an error at getgrid");
		exit(1);
	}
	else
	{
		gid = grp->gr_name;
		std::cout << gid << " ";
	}
	return;
}

void printl(vector<string> d) //case l
{
	int i = 0;
	struct stat sfiles;
	std::cout <<"Total " << std::endl;
	while(d[i] != "\0")
	{
		//if(sfiles != '.')
		//if file doesn't have a dot in front, print following
		printPermissions();	//print permissions
	
//		printlinfo(sfiles);	//print getinfo 

		std::cout << std::setw(5) << std::right;
		std::cout<< sfiles.st_size << " ";

		printdate(sfiles);		//print date
		printlfcolor((char*)d[i].c_str());//print file

		printf("\n");
		i++;
	}
}
#endif
