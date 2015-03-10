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

using namespace std;

void pcolor(struct stat s, dirent * dirtp)
{
	string black = "\033[30m";
	string green = "\033[32m";
	string blue = "\033[34m";
	if(s.st_mode & S_IFDIR) //blue
	{	
		cout << blue << dirtp->d_name << flush;
		cout << black <<"/" << flush;
	}
	else if ((s.st_mode & S_IXUSR))//green
	{
		cout << green << dirtp->d_name << flush;
		cout << black <<"*" << flush;
	}
	else//black
	{
		cout << black << dirtp->d_name << flush;
	}
}

#endif
