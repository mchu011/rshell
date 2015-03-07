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

void remelem(char** a, int pos)
{
	string input;
	vector<char*> arg;
	bool rflag = false;
	
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
	
void movef(char** a, int pos, int csz)
{
//need to check directories/paths
	int sz = csz - pos;
	int d, old;
	if(sz == 2)
	{
		char * oldfile = a[csz - 2];
		char * newfile = a[csz - 1];

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
	int size = 0;
	for(;arg[size];size++) {}
	for(int k = 0; k < ; k++)
	{
		if(strstr(arg[k], "rm") != NULL)
		{
			int hold = k+1;
			remelem(arg, hold);
		}
		else if(strstr(arg[k], "mv") != NULL)
		{
			int hold = k+1;
			movef(arg, hold, size);
		}
	}
	
}

