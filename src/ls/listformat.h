#ifndef FLAGL_H
#define FLAGL_H

#include <stdio.h>
#include <stdlib.h>	//needs to have color
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
#include "ignoredots.h"
using namespace std;

void printPermissions(const struct stat &s)
{
	if(s.st_mode & S_IFDIR) cout << "d";  //directory
	else if(s.st_mode & S_IFLNK) cout << "l";//link
	else if(s.st_mode & S_IFREG) cout << "-";
	else if(s.st_mode & S_IFCHR) cout << "c";
	else if(s.st_mode & S_IFBLK) cout << "b";
	else if(s.st_mode & S_IFIFO) cout << "f";
	else if(s.st_mode & S_IFSOCK) cout << "s";
	else cout << "-";

	printf((s.st_mode & S_IRUSR) ? "r" : "-"); //users
	printf((s.st_mode & S_IWUSR) ? "w" : "-");
	printf((s.st_mode & S_IXUSR) ? "x" : "-");
	printf((s.st_mode & S_IRGRP) ? "r" : "-"); //group
	printf((s.st_mode & S_IWGRP) ? "w" : "-");
	printf((s.st_mode & S_IXGRP) ? "x" : "-");
	printf((s.st_mode & S_IROTH) ? "r" : "-"); //others
	printf((s.st_mode & S_IWOTH) ? "w" : "-");
	printf((s.st_mode & S_IXOTH) ? "x" : "-");

	return;
}

void printdate(const struct stat &s)
{
	time_t comptim= s.st_mtime;
	
	tm *t = localtime(&comptim);
	/*if(localtime_r(&comptim, &t) == '\0')
	{
		perror("There's a problem with localtime");
	}*/

	char timout[50];


	strftime(timout, 50, "%h", t);
	std::cout << timout << " ";	
	
	strftime(timout, 50, "%d", t);
	std::cout << timout << " ";	

	strftime(timout, 50, "%R", t);
	std::cout << timout << " ";	
	return;
}

void printlinfo(const struct stat &s)		//error in this by pw_name and gr_name
{
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

	if(!(grp = getgrgid(s.st_gid)))
	{
		perror("There's an error at getgrid");
		exit(1);
	}
	else
	{
		gid = grp->gr_name;
		cout << gid << " " << flush;
	}
	return;
}

int maxsz(const struct stat &s, vector<string> d)
{
	int count = 0;
	int size, k;
	for(k = 0; d[k] != "\0"; k++)
	{
		size = s.st_size;
		count += size/10000000;
	}
	
	return count/k;	
}

void printl(bool &ig) //case l
{
	char* dirName =(char*)"."; //this is to get current directory
	DIR* directory;
	directory = opendir(dirName);
	dirent *dirtpoint;
	vector<string> dirfiles;
				
	while((dirtpoint = readdir(directory))) //save dirctory names
	{
		if(errno != 0)
		{
			perror("there's a problem in read dir");
			exit(1);
		}

		dirfiles.push_back(dirtpoint->d_name);//gets filename
	}

	sort(dirfiles.begin(), dirfiles.end(),locale("en_US.UTF-8"));//sorts files

	if(ig)	//takes out dot files
	{
		dirfiles = takeoutdots(dirfiles);
	}
	dirfiles.push_back("\0");

	std::cout <<"Total: "; //<< std::endl;

	struct stat sfiles;
	int c = maxsz(sfiles, dirfiles);	
	cout << c << endl;
	
	int i = 0;
	while(dirfiles[i] != "\0")
	{
		if(dirfiles[i] == "\0")
		{
			break;
		}
		struct stat sfiles;
		char filepath[1024];
		strcpy(filepath, dirName);
		strcat(filepath, "/");
		strcat(filepath, dirfiles[i].c_str());

		if((stat(filepath, &sfiles)) == -1)
		{
			perror("there's an issue with stat prinl");
		}

		int size = 0;
		
		if(ig) //if dots need to be taken out
		{
			if(dirfiles[i][0] == '.')
			{
				//skip dots		
			}
			else
			{
				printPermissions(sfiles);//print permissions
				cout << " "<< sfiles.st_nlink << " ";
				printlinfo(sfiles);	//print getinfo 
				size = sfiles.st_size;
				cout << setw(7) << right << size << " ";
				printdate(sfiles);		//print date
				cout << dirfiles[i] << flush;	
				//pcolor(sfiles, dirtpoint);//print file
				printf("\n");
			}
	
		}
		else
		{
			printPermissions(sfiles);//print permissions
			cout << " "<< sfiles.st_nlink << " ";
			printlinfo(sfiles);	//print getinfo 
			size = sfiles.st_size;
			cout << setw(5) << right << size << " ";
			printdate(sfiles);		//print date
			cout << dirfiles[i] << flush;	
			//pcolor(sfiles, dirtpoint);//print file
			printf("\n");
		}
		i++;
	}

	if(closedir(directory) == -1)
	{
		perror("there's a problem in closedir");
		exit(1);
	}
}
#endif
