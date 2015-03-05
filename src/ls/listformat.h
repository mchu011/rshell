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

#include "color.h"
using namespace std;

void printPermissions()
{
	struct stat s;
	if(s.st_mode & S_IFDIR) cout << "d";
	else if(s.st_mode & S_IFLNK) cout << "l";
	else if(s.st_mode & S_IFREG) cout << "-";
	else if(s.st_mode & S_IFCHR) cout << "c";
	else if(s.st_mode & S_IFBLK) cout << "b";
	else if(s.st_mode & S_IFIFO) cout << "f";
	else if(s.st_mode & S_IFSOCK) cout << "s";
	else cout << "-";

	printf((s.st_mode & S_IRUSR) ? "r" : "-");
	printf((s.st_mode & S_IWUSR) ? "w" : "-");
	printf((s.st_mode & S_IXUSR) ? "x" : "-");
	printf((s.st_mode & S_IRGRP) ? "r" : "-");
	printf((s.st_mode & S_IWGRP) ? "w" : "-");
	printf((s.st_mode & S_IXGRP) ? "x" : "-");
	printf((s.st_mode & S_IROTH) ? "r" : "-");
	printf((s.st_mode & S_IWOTH) ? "w" : "-");
	printf((s.st_mode & S_IXOTH) ? "x" : "-");

	return;
}

void printdate()
{
	struct stat s;
	time_t comptim= localtime(&(s.st_mtime))
	struct tm *t;
	
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

void printlinfo()		//error in this by pw_name and gr_name
{
	struct stat s;
	string uid, gid;
	struct group* grp;

	if(getlogin() == NULL)	//if no login name
	{	
		string name = "unknown";
		uid = name;
	}
	else		//gets username
	{
		uid = getlogin();
	}
	cout << uid << " " << flush;

	/*if(!(grp = getgrgid(s.st_gid)))
	{
		perror("There's an error at getgrid");
		exit(1);
	}
	else
	{
		gid = grp->gr_name;
		cout << gid << " " << flush;
	}*/
	return;
}

void printl(vector<string> d) //case l
{
	int i = 0;
	struct stat sfiles;
	std::cout <<"Total: " << std::endl;

	while(d[i] != "\0")
	{
		printPermissions();	//print permissions
		
		cout << " "<< sfiles.st_nlink << " ";
	
		printlinfo();	//print getinfo 

		std::cout << std::setw(5) << std::right;
		std::cout<< sfiles.st_size << " ";

		printdate();		//print date
		printlfcolor((char*)d[i].c_str());//print file

		printf("\n");
		i++;
	}
}
#endif
