#ifndef CMDLEXEC_H	//looks for cd, ls, and cp commands
#define CMDLEXEC_H	//executes redirection ( >, >>, <, and |)
			//returns true if process can be executed
#include <unistd.h>
#include <string.h>	//need to:
#include <stdio.h>	//figure out cd "home" stuff and functions
			//complete executions of each demand
#include "cp.h"

using namespace std;

void redircmd(char** a, bool &firstc)
{
	char** execute;		//checks for redirection commands
	execute = new char*[50];
	int p = 0;
	int e = 0;
	for(; a[p]; p++)
	{
		if(strcmp(a[p], ">") == 0) //redirect and overwrites fd to 
		{ //uses int ec                                     //file on the right
		
 		}
        	else if(strcmp(a[p], "<") == 0) //accept input from file on right
	        {//uses int ec
				
	       	}
        	else if(strcmp(a[p], "|") == 0)//pipes command
		{
				
        	}
		else if(strcmp(a[p], ">>") == 0) //redirect and append fd to
	        {//uses int ec                                       //file on right
 			
	        }
		else
		{
			execute[e] = a[p];	//assigns string of before to execute
			e++;
		}
	}
	execute[e] = '\0';
	

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
                	char *tohome = getenv("HOME");  //issue here
                        if(chdir(home) == -1)	//FIXME
                        {
                        	perror("theres an error in chdir1");
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
	return;
}
#endif
