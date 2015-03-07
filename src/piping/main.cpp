#include <iostream>		//still needs to be edited
#include <unistd.h>		//connectors execution issue			
#include <stdio.h>		// of && and ||	 	
#include <string.h>			
#include <sys/types.h>		//FIXME pipe.h modification
#include <sys/wait.h>		//add redirect file content
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdlib>
#include <pwd.h>
#include <vector>
#include <errno.h>

#include "parser.h"
#include "gethostname.h"
#include "getusername.h"
#include "execute.h"
#include "cntexec.h"
#include "exit.h"
#include "pipe.h"
#include "cp.h"
#include "cmdLexec.h"
#include "redirect.h"
#include "background.h"

using namespace std;
	
int main ()
{
	char *pathval = getenv("PATH");//get path info
	char *prsPth[50];
	parsepath(pathval, prsPth);//save path value

	char*  username;//get host and user name
	char  hostname[25];
	getusername(username);
	gethnm(hostname);	
	
	string cmdLn;	//information for 
	char cmd[BUFSIZ];//running code
	char buf[BUFSIZ];//more than once
	char** args;
	int pars;
	bool bkgck = false;

	while (1) 
	{
		if(!getcwd(buf, BUFSIZ))//headers for path command
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

			pars = parseCmd(cmd, args);//parse into tokens for args
						//returns args size to pars
			bkgck = bgd(pars, args); //check background processes

			cnctexec(args, bkgck, prsPth);//execute
			
			bkgck = false; //reset background vals
		}
		//sleep(1);//pause 1 sec
		delete[] args;
	}

	return 0;
}
