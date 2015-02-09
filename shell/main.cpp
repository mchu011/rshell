#include <iostream>		//still needs to be edited
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <cstdlib>
#include <pwd.h>

using namespace std;

char* getusername()
{
		
}

char* gethostname()
{
	
}

char** parseCmd(string s)
{
	char* c = (char*)s.c_str();
	char* clist;
	int k = 0;
	int j = 0;
	for(j; c[j]; j++)	//for no space connectors
	{
		if(c[j] == ';')
		{
			if (c[j-1] != ' ')
			{
				clist[j+k] = ' ';
				k++;
			}
			
			clist[j+k] = c[j];
			k++;
			if(c[j+1] != ' ')
			{
				clist[j+k] = ' ';
				k++;
			}	
		}
		else if(c[j] == '&')
		{
			if(c[j+1] == '&')
			{
				if(c[j-1] != ' ')
				{
					c[j+k] = ' ';
					k++;
				}	
				clist[j+k] = c[j];
				j++;
				clist[j+k] = c[j];
				k++;
				if(c[j+1] !=  ' ')
				{
					clist[j+k] = ' ';
					k++;
				}
			}
			else
			{
				clist[j+k] = c[j];
				k++;
			}
		}
		else if(c[j] == '|')
		{
			if(c[j+1] == '|')
			{
				if(c[j-1] != ' ')
				{
					clist[j+k] = ' ';
					k++;
				}
				clist[j+k] = c[j];
				j++;
				clist[j+k] = c[j];
				k++;
				if(c[j+1] != ' ')
				{
					clist[j+k] = ' ';
					k++;
				}
			}
		}
		else
		{
			clist[j+k] = c[j];
		}
	}
	clist[j+k] = ' ';
	clist[j+k+1] = '\0';	
	char** tokenlist;
	tokenlist[0] = strtok(clist, " ");
	for(int i = 1; clist[i];i++)
	{
		tokenlist[i] = strtok(NULL, " ");
	}
	
	return  tokenlist;	
}


int main ()
{
	//stat struct s;
	char*  username;
	char*  hostname;
	struct passwd *pw;
	//if(!(pw = getpwuid(s.st_uid)))
	//	perror("there's and error in getpwid");
	//username = getusername();
	//hostname = gethostname();	

	while (1) 
	{
		int child;	//child Pid
		string cmdLn;	//command line

		getline(cin, cmdLn);
		//cout << username << "@" << hostname;
		printf("$ ");			//print command line
		std::cout << cmdLn << std::endl;
		
		char** cmd;
		cmd = parseCmd(cmdLn);	//parse command
		
		int status;
		child = fork();
		
		if(child == -1)
		{
			perror("there's an error with fork().");
			exit(1);
		}
		else if(child == 0)
		{
			//cout << "executing" << endl;
			if(execvp(cmd[0],cmd) == -1)	//issue executing command
			{
				perror("there's an error on execvp.");
				//exit(1);	//something about bad address
			}
			exit(1);
			//execvp(cmd[0], cmd);
		}
		else		//parent function
		{
			//cout << "parent function" << endl;
			if(waitpid(child, &status, 0) == -1)
			{
				perror("there's an error with wait().");
			}
		}
	}

	return 0;
}
