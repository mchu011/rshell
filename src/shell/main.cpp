#include <iostream>		//still needs to be edited
#include <unistd.h>		//connectors execution issue			
#include <stdio.h>		// of && and ||	 	
#include <string.h>			
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdlib>
#include <pwd.h>
#include <vector>

#include "parser.h"
#include "gethostname.h"
#include "getusername.h"
#include "execute.h"
#include "cntexec.h"
#include "exit.h"

using namespace std;
	
int main ()
{
	char*  username;
	char  hostname[25];
	getusername(username);	//getusername
	gethnm(hostname);	//gethostname
	
	string cmdLn;	//command line
	char cmd[BUFSIZ];
	char buf[BUFSIZ];
	char** args;

	while (1) 
	{
		if(!getcwd(buf, BUFSIZ))	//headers
		{
			perror("getcwd");
		}
		cout << buf << endl;	
		cout << username << "@" << hostname;
		printf(" $ ");			//print command line

		getline(cin, cmdLn); //get command
		addspace(cmdLn);   //add spaces to connectors
		strcpy(cmd, cmdLn.c_str());	//copy into a char pointer
		
		exitcode(cmd);	//exit if phrase is exit

		if(strcmp(cmd, "") != 0)//if the command is null	
		{
			args = new char*[50];	//allocate new char** array

			parseCmd(cmd, args);	//parse into tokens
						//and save into args
			cnctexec(args);
		}
		//sleep(1);//pause 1 sec
		delete[] args;
	}

	return 0;
}
