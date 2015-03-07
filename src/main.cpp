#include <iostream>		//still needs to be edited
#include <unistd.h>		//connectors execution issue			
#include <stdio.h>		//signals		 	
#include <string.h>		//rm file	
#include <sys/types.h>		//move executions to execute
#include <sys/wait.h>		
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdlib>
#include <pwd.h>
#include <vector>
#include <signal.h>

#include "parser.h"
#include "gethostname.h"
#include "getusername.h"
#include "execute.h"
#include "cntexec.h"
#include "exit.h"
#include "signals.h"
#include "cd.h"
#include "cp.h"
#include "ls.h"
#include "mvrm.h"

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
	int size = 0;

	while (1) 
	{
		signal(SIGINT, sigc); //signal catchers
		//signal(SIGTSTP, sigz);

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

		
		if(strcmp(cmd, "") != 0) //if string is not empty 	
		{
			args = new char*[50];	//allocate new char** array
			
			size = parseCmd(cmd, args);	//parse into tokens
							//and save into args
			if(size == 2 && strcmp(args[0], "cd") == 0)
			{
				cdpath(args); //go to new path of cd
			}			//and only two variables
			else
			{
				cnctexec(args); //go to execution
			}
		}

		sleep(1);//pause 1 sec
		delete[] args;
		size = 0;
	}

	return 0;
}
