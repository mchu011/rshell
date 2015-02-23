#ifndef CMDLEXEC_H	//looks for cd, ls, and cp commands
#define CMDLEXEC_H	//executes redirection ( >, >>, <, and |)
			//returns true if process can be executed
#include <unistd.h>
#include <string.h>	//need to:
#include <stdio.h>	//figure out cd "home" stuff and functions
			//complete executions of each demand
#include "cp.h"
#include "pipe.h"

using namespace std;

void redircmd(char** a, bool &firstc, bool pip)
{
	char** execute;		//checks for redirection commands
	execute = new char*[50];
	int p = 0;
	int e = 0;
	for(; a[p]; p++)
	{
		if(strcmp(a[p], ">") == 0) //redirect and overwrites fd to 
		{ //uses int ec                                     //file on the right
			execute[e] = '\0';
			if(execute[0] == "0" || execute[0] == "1" || execute[0] == "2")
			{
					
			}	
			// else if a file or directory
			//else say if it is a command 
 		}
        	else if(strcmp(a[p], "<") == 0) //accept input from file on right
	        {//uses int ec
			execute[e] = '\0';

				
	       	}
		else if(strcmp(a[p], ">>") == 0) //redirect and append fd to
	        {//uses int ec                                       //file on right
			execute[e] = '\0';

 			
	        }
        	else if(strcmp(a[p], "|") == 0)//pipes command
		{
			execute[e] = '\0';//gets part 1 of pipe
			
			char**scndprt;
			scndprt = new char*[50];
			int k = 0;
			for(;a[p]; p++)
			{
				scndprt[k] = a[p];
				k++;
			}
			scndprt[k] = '\0';
			
			pipexec(execute, scndprt, pip);

			delete[] scndprt;
        	}
		else
		{
			execute[e] = a[p];	//assigns string of before to execute
			e++;
		}
	}
	
	delete[] execute;

	return;
}

void checkcmd(char** a)
{
	int Asize = 1;
	for(;a[Asize]; Asize++)	//count the size of the string array
	{ }

	if(strcmp(a[0], "cd") == 0) //check if command is cd
	{	
       	 	if(Asize == 2) // if the size 
        	{
			if(execvp(a[0],a) == -1)
			{
				perror( "there's an error in cd execvp");
			}
                }
                else
                {
                       	if(chdir(a[1]) == -1);
                        {
                         	perror("error in chdir.");
                        }
                }
	}
	else if(strcmp(a[0], "ls") == 0) //check if command is ls
	{

	}
	else if(strcmp(a[0], "cp") == 0)	//check if command is cp
	{
		if(Asize == 2)
		{
			cprwbuf(a[1], a[0]);	
		}
		else
		{
			cout <<"too many arguments for cp" << endl;
		}
	}
	else if(strcmp(a[0], "cat") == 0)
	{
		for(int k = 1; a[k]; k++)
		{
			cout << a[k];
		}
		cout << endl;
	}
	else if(strcmp(a[0], "echo") == 0)
	{
		for(int k = 1; a[k]; k++)
		{
			cout << a[k];
		}
		cout <<endl;
	}
	return;
}
#endif
