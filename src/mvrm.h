#ifndef MVRM_H
#define MVRM_H

#include <unistd.h>
#include <stdlib.h>	//working on moving into directories
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <vector>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

void recdel(string dirnme)
{
	vector<string> indir;
	DIR* dir;
	struct dirent *drnt;
	
	if(dir = opendir(dirnme.c_str()))
	{
		while (drnt = readdir(dir))
		{
			if(strcmp(".", drnt->d_name) != 0 &&
				 strcmp("..",drnt->d_name) != 0)
			{
				indir.push_back(dirnme + "/" + drnt->d_name);
			}
		}
	}
	else
	{
		perror("close dir rm");
	}
	
	if(indir.size() == 0)
	{
		cout << "file directory is not empty" << endl;
	}
	struct stat file2;
	for(int i = 0; i < indir.size(); i++)
	{
		char* cdir = (char*)indir[i].c_str();	
		if(stat(cdir, &file2) != 0)
		{
			perror("error in stat indir");
		}
		if(S_ISDIR(file2.st_mode))
		{
			recdel(indir.at(i));
			rmdir(indir.at(i).c_str());
		}
		else
		{
			if(unlink(indir.at(i).c_str()) == -1)
			{
				perror("Error in removing dir");
			}
		}
	}
	return;	
}
			

void remelem(char** a)
{
	string input;
	vector<char*> arg;
	bool rflag = false;

	if(strcmp(a[0], "rmdir") == 0) //check if rmdir
	{
		rflag = true;
	}

	int p = 0;
	while(a[p] != NULL) //save a as local arg
	{
		arg.push_back(a[p]);
	}

	
	if(rflag)
	{
		struct stat file;
		for(int i = 1; i < arg.size(); i++)
		{
			if(stat(arg.at(i), &file) != 0)
			{
				perror("error at file stat");
			}
			if(S_ISDIR(file.st_mode))
			{
				string dirnam = string(arg.at(i));
				recdel(dirnam);
				rmdir(dirnam.c_str());
			}
			else
			{
				unlink(arg.at(i));
			}
		}
	}
	else
	{
		struct stat files;
		for(int i = 1; i < arg.size(); i++)
		{
			if(stat(arg.at(i), &files) != 0)
			{
				perror("error at file stat");
			}
			if(S_ISDIR(files.st_mode))
			{
				if(rmdir(arg.at(i)) == -1)
				{
					perror("rmelem else S_ISDIR");
				}
			}
			else
			{
				unlink(arg.at(i));
			}
		}
	}
					
	
		
	/*int k = 0;
	while(arg[k]) //looks for r for remove directory
	{
		if(arg[k][0] == '-') 
		{
			if(strstr(arg[k], "r") == 0)
			{
				rflag = true;
			}
		}
	}
			
	if(rflag)
	{
		struct stat file;
		for(int i = )	
	}*/
	/*if(strstr(a[pos], "-r") != NULL)//remove directory
	{
		string path = a[pos +1]; //makes path into directory
		path += "/";
		
		rmdir(path.c_str());
	}
	else	//remove file(s)
	{*/
		/*int k = pos;
		for(;a[k]; k++);
		{
			string r = a[k];
			unlink(r.c_str());
		}
	}*/
	//check if name is a file/dir
	//
}

int isdir(char*str) //checks if file is a directory or not
{
	DIR *dir;
	
	if(access(str,0) != 0)
	{
		return -1;
	}
	
	dir = opendir(str);

	if(dir != NULL) //returns directory
	{
		closedir(dir);
		return 1;
	}
	return 0; //returns file
}
	
void movef(char** a, int sz)
{
	sz--;
//need to check directories/paths
	int d, old;
	if(sz == 2)
	{
		char * oldfile = a[1];
		char * newfile = a[2];

		//check if string is directory
		old = isdir(oldfile);
		d = isdir(newfile);
		
		if(old == -1)
		{
			perror("file doesn't exist");
			exit(1);
		}

		char* dirName = (char*)".";
		DIR* dir;
		dir = opendir(dirName);
		dirent *direntp;
		vector<string> directory;

		while((direntp = readdir(dir)))
		{
			if(strcmp(newfile, direntp->d_name) == 0)
			{
				perror("file name already exists");
				exit(1);
			}
		}
		
		directory.push_back("\0");
		int i = 0;
		//search current directory if same as newfile


		if(d == 1 && old == 1) //if both are directories
		{
			rename(oldfile, newfile); //changes directory name	
		}
		else if(d == 1)	//if put file into new directory
		{
			//change newfile into directory
			string path = newfile; //makes path into directory
			path += "/";
			path += oldfile;
			
			link(oldfile, path.c_str());	
		}
		else	//changes files	
		{
			link(oldfile, newfile); //link filenames
			//rename(oldfile, newfile); //or you can do this
		}
		unlink(oldfile);	
		closedir(dir);
	}
	else if(sz < 2)
	{
		printf("need a destination file\n");
	}
	else if(sz > 2)
	{
		printf("too many files\n");
	}
	return;

}

void mvrm(char** arg)
{
	if(strstr(arg[0], "rm") != NULL)
	{
		remelem(arg);
	}
	else if(strcmp(arg[0], "mv") == 0)
	{
		int size = 0;
		for(;arg[size];size++) {}
		movef(arg, size);
	}
	
}
#endif
