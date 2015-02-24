#ifndef GETUSERNAME_H
#define GETUSERNAME_H

#include <iostream>
#include <cstdlib>
#include <pwd.h>
#include <string.h>
using namespace std;			//gets username of the system
void getusername(char* &u)		//and returns address reference
{
	if(getlogin() == NULL)	//if no login name
	{
		perror("No username");
		char* name = (char*)"unknownUser";
		u = name;
	}
	else		//gets username
	{
		u = getlogin();
	}
	return;
}
#endif
