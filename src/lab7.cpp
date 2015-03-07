#include <unistd.h>
#include <stdlib.h>	//working on moving into directories
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

using namespace std;

void remelem(char** a, int pos)
{
	if(strstr(a[pos], "-r") != NULL)//remove directory
	{
		/*string path = a[pos +1]; //makes path into directory
		path += "/";
		
		rmdir(path.c_str());*/
	}
	else	//remove file(s)
	{
		/*int k = pos;
		for(;a[k]; k++);
		{
			string r = a[k];
			unlink(r.c_str());
		}*/
	}
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

	if(dir != NULL)
	{
		closedir(dir);
		return 1;
	}
	return 0;
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
		}
		unlink(oldfile);	
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

int main(int argc, char** argv)
{
	for(int k = 0; k < argc; k++)
	{
		if(strstr(argv[k], "rm") != NULL)
		{
			int hold = k+1;
			remelem(argv, hold);
		}
		else if(strstr(argv[k], "mv") != NULL)
		{
			int hold = k+1;
			movef(argv, hold, argc);
		}
	}
	
	return 0;
}

