#include <iostream>		//still needs to be edited
#include <unistd.h>			//connectors issue in connector code execution
#include <stdio.h>			//fix parse cmd 	
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
	
	int child;	//child Pid
	string cmdLn;	//command line
	char cmd[BUFSIZ];
	int status;//for parent function
	char buf[BUFSIZ];
	bool emptystr = false;
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

		if(strcmp(cmd, "") == 0)	
		{
			emptystr = true;
		}
		args = new char*[50];

		parseCmd(emptystr, cmd, args);	//parse command into tokens FIXME

		for(int k = 0; args[k] != NULL; k++)
		{
			cout << args[k] << endl;
		}
		return 0;		

		child = fork();
		
		if(child == -1)
		{
			perror("there's an error with fork().");
			exit(1);
		}
		else if(child == 0)
		{
			//myexec(cmd); //error in executing connectors
			exit(0);
		}
		else		//parent function
		{
			if(waitpid(child, &status, 0) == -1)
			{
				perror("there's an error with wait().");
			}
		}
		sleep(1);
		emptystr = false;
		delete[] args;
	}

	return 0;
}
