#include <iostream>		//still needs to be edited
#include <unistd.h>			//connectors issue in connector code execution
#include <stdio.h>			
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdlib>
#include <pwd.h>

#include "parser.h"

using namespace std;

void cnctexec(char** str)
{
	char** args;
	int i = 0;
	int j = 0;
	for(;str[i] != '\0'; i++)
	{
		exitcode(args[j]);		//exit code
		if(strcmp(str[i],";") == 0)
		{	
			if(execvp(args[0],args) == -1)
			{
				perror("there's an error on execvp.");
				exit(1);
			}
			else
			{
				char** rep;
				i++;
				i++;
				int k;
				for(k = 0; str[i];k++)
				{
					rep[k] = str[i];
					i++;
				}
				rep[k] = '\0';
				cnctexec(rep);
				return;
			}
			
		}
		else if(strcmp(str[i+1], "&&") == 0)	//if first is true then execute second
		{
			
			if(execvp(args[0],args) == -1)	//issue executing command with connectors
			{
				perror("there's an error on execvp.");
				i++;
				i++;
			}
			else
			{
				char** rep;
				i++;
				i++;
				int k;
				for(k = 0; str[i];k++)
				{
					rep[k] = str[i];
					i++;
				}
				rep[k] = '\0';
				cnctexec(rep);
				return;
			}
			/*if(istrue(str[i-1]))
			{
				i++;
				args[j] = str[i];
				j++;
			}
			else
			{
				j--;	
			}*/
		}
		else if(strcmp(str[i+1], "||") == 0)	//if first is false then use second
		{
			if(execvp(args[0],args) == -1)	//issue executing command with connectors
			{
				perror("there's an error on execvp.");
				
				char** rep;
				i++;
				i++;
				int k;
				for(k = 0; str[i];k++)
				{
					rep[k] = str[i];
					i++;
				}
				rep[k] = '\0';
				cnctexec(rep);
				return;
			}
			else
			{
				i++;
				i++;
			}
			
		/*	if(istrue(str[i-1]))
			{
				i++;
			}
			else
			{
				j--;
				i++;
				args[j] = str[i];
				j++;
			}*/
		}
		else
		{
			args[j] = str[i];
			j++;
		}
	}
	args[j] = '\0';
	
	if(execvp(args[0],args) == -1)	//issue executing command with connectors
	{
		perror("there's an error on execvp.");
		exit(1);
	}
	return;
}
	
int main ()
{
	struct stat s;
	char*  username;
	char  hostname[100];

	if(getpwuid(s.st_uid))
	{
		perror("there's and error in getpwid");
		exit(1);
	}
	
	if(getlogin() == NULL)				//get username
	{
		perror("No username");
		char* name = (char*)"unknownUser";
		username = name;
	}
	else
	{
		username = getlogin();
	}
	
	if(-1 == gethostname(hostname, sizeof(hostname)-1))		//get hostname
	{
		perror("There's a problem in gethostname");
		exit(1);
	}

	for(int i = 0; hostname[i]; i++)
	{
		if(hostname[i] = '.')
		{
			hostname[i] = '\0';
		}
	} 
	
	int status;
	int child;	//child Pid
	string cmdLn;	//command line
	char* cmdncmt;
	char**  cmd;

	while (1) 
	{

		getline(cin, cmdLn);
		cout << username << "@" << hostname;
		printf("$ ");			//print command line
		cout << cmdLn << endl;
	
		cmdncmt = cmtout((char*)cmdLn.c_str());	//keep out comments
		exitcode(cmdncmt);		//exit code
		
		cmd = parseCmd(cmdncmt);	//parse command

		child = fork();
		
		if(child == -1)
		{
			perror("there's an error with fork().");
			exit(1);
		}
		else if(child == 0)
		{
			cnctexec(cmd);
			exit(0);
		}
		else		//parent function
		{
			if(waitpid(child, &status, 0) == -1)
			{
				perror("there's an error with wait().");
			}
		}
	}

	return 0;
}
