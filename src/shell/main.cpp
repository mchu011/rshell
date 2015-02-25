#include <iostream>		//still needs to be edited
#include <unistd.h>			//connectors issue in connector code execution
#include <stdio.h>			//fix parsers:keeps returning garbage	
#include <string.h>			//once it reacehs connectors
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdlib>
#include <pwd.h>

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
	char**  cmd;
	int status;//for parent function
	char buf[BUFSIZ];

	while (1) 
	{
		if(!getcwd(buf, BUFSIZ))	//headers
		{
			perror("getcwd");
		}
		cout << buf << endl;	
		cout << username << "@" << hostname;
		printf(" $ ");			//print command line

		getline(cin, cmdLn);
		
		cmd = parseCmd(cmdLn);	//parse command

		child = fork();
		
		if(child == -1)
		{
			perror("there's an error with fork().");
			exit(1);
		}
		else if(child == 0)
		{
			myexec(cmd); //error in executing connectors
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
	}

	return 0;
}
