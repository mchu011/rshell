#ifndef GETUSERNAME_H
#define GETUSERNAME_H

#include <iostream>
#include <cstdlib>
#include <pwd.h>
#include <string.h>
using namespace std;
void getusername(char* &u)
{
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
}
#endif
