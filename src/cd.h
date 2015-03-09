#ifndef CD_H
#define CD_H

#include <unistd.h>	//changes directories
#include <iostream>
#include <string.h>

#include "parser.h"
using namespace std;

void cdpath(char** cdstr) // works
{
	int cnt = 0;
	for(int q = 0; cdstr[q]; q++)
	{
		cnt++;
	}
	
	if(cnt == 2)	//not working for some reason
	{
		char curpath[BUFSIZ];
		if(!getcwd(curpath, BUFSIZ))//get current dir
		{
			perror("getcwd");
		}

		string path = curpath;//change directory
		path+= "/";
		path+= cdstr[1];
	
		if(chdir(path.c_str()) == -1)
		{
			perror("error in chdir path");
		}
		
		if(!getcwd(curpath, BUFSIZ))	//output new directory
		{
			perror("getcwd");
		}
		cout << curpath << endl;	
		//link(curpath, path.c_str());
		//unlink(curpath);		
	}
	else if(cnt == 1)
	{
		char* gohome = getenv("HOME");
		if(chdir(gohome) == -1)
		{
			perror("error in chdir home");
		}
	}
	else
	{
		perror("too many arguments");
	}
	return;
}

#endif
