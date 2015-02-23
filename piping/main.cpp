#include <iostream>	//still needs to be edited FIXME
#include <unistd.h>		//connectors issue in connector code execution
#include <stdio.h>		//need to: 			
#include <string.h>		//figure out what happened with delete
#include <sys/types.h>		//reread dup and piping	
#include <sys/wait.h>		//incorporate piping into main code
#include <sys/stat.h>		
#include <fcntl.h>		//segfault issue for header codes?
#include <cstdlib>
#include <pwd.h>
#include <algorithm>

#include "parser.h"
#include "getusername.h"
#include "gethostname.h"
#include "cmdLexec.h"		//compiler issues here FIXME
#include "execute.h"		//connector code: hope it connects
#include "cp.h"

using namespace std;

int main ()
{
	char*  username;
	char  hostname[25];
	getusername(username);	//get username
	gethnm(hostname);	//get hostname
	
	int status;
	int child;	//child Pid
	string cmdLn;	//command line recieve
	char* cmdncmt;	//command to be parsed
	char buf[BUFSIZ];
	bool bgck = false;

	while (1) 
	{
		if(!getcwd(buf, BUFSIZ))	//perror
		{
			perror("problem with getcwd");
		}
		cout << buf << endl;

		cout << username << "@" << hostname; //print command line
		printf(" $ ");		
		getline(cin, cmdLn);	//get line from user

		cmdncmt = cmtout((char*)cmdLn.c_str());	//takes comments out
		exitcode(cmdncmt);		//if the string is 'exit' only
		
		bool emptycmd = false;
		if(!strcmp(cmdncmt,"")) emptycmd = true; //check if empty
		

		char**  cmd;	//parsed command
		cmd = new char*[100];
		
		parseCmd(cmdncmt,cmd,emptycmd);	//parse command
		
		bgck = false;
		bgck = bgd(pars,cmd, emptycmd);	//check if there's a background process

		child = fork();	//fork child
		
		if(child == -1)	//perror check
		{
			perror("there's an error with fork().");
			exit(1);
		}
		else if(child == 0)	//child function
		{
			cnctexec(cmd, bgck);//go into connector executions
			exit(0);
		}
		else		//parent function
		{
			if(waitpid(child, &status, 0) == -1)
			{
				perror("there's an error with wait().");
			}
		}
		delete[] cmd;//free memory //FIXME issue with free in debug
	}

	return 0;
}
