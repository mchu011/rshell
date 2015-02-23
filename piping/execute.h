#ifndef EXECUTE_H			
#define EXECUTE_H			//distinguishes separate commands from connectors
					//and sends redirector, pipe, and cp, ls
#include <unistd.h>			//to next cmdlexec functions
#include <stdio.h>
#include <string.h>			//need to fix execution error

#include "cmdLexec.h"

using namespace std;

bool bgd(int arg, char** cmd, bool empty) //checks for background processes
{
	bool backgrdck = false;
	if(arg > 0) arg--;
	
	if(empty == false && strcmp(cmd[arg], "&") == 0)
	{
		backgrdck = true;
		cmd[arg] =  NULL;
	}
	else if(empty == false)
	{
		char* checker = cmd[arg];
		int clen = strlen(cmd[arg]) - 1;
		if(checker[clen] == '&')
		{
			backgrdck = true;
			checker[clen] = '\0';
			cmd[arg] = checker; 
		}
	}
	return backgrdck;
}

void cnctexec(char** str, bool piper){		//first copy execution list into local
					//list to determine execution
        char** args;	
        args = new char*[50];
	
	bool rdir = false;
	bool firstcmd = false;
	int i = 0;
        int j = 0;
        for(;str[i] != '\0'; i++)       //parse through char pointer array for connectors
        {
                if(strcmp(str[i],";") == 0)	//';' execute and continue
                {				
			args[j] == '\0';			

			if(args[0] == "cd" || args[0] == "ls" || args[0] == "cp" || args[0] == "cat" || args[0] == "echo") // checks command arguments
			{
				checkcmd(args);
			}
			
			for(int k = 0; args[k]; k++)	//checks if args is redirect or pipe
			{
				if(args[k] == ">" || args[k] == ">>" || args[k] == "<" || args[k] == "|")
				{
					redircmd(args, firstcmd, piper);	//goes to execute redirect or pipe command
					rdir = true;
				}
			}

			if(rdir)	//if args is a redirected command
			{
				rdir = false;	// reset rdir
			}
			else		// if args is not a redirected command
			{
                       		if(execvp(args[0],args) == -1)//execute whatever args is
                        	{
                                	perror("there's an error on ; execvp.");//error checking
                                	exit(1);
                      		}
			}
			firstcmd = false;
			delete[] args;	//reset args
			args = new char*[50];
			j = 0;

                }	
                else if(strcmp(str[i], "&&") == 0)// "&&": execute second if first true
		{	
			args[j] == '\0';

			if(args[0] == "cd" || args[0] == "ls" || args[0] == "cp" || args[0] == "cat" || args[0] == "echo") // checks command arguments
			{
				checkcmd(args);
			}

			for(int k = 0; args[k]; k++)	//checks if args is redirect or pipe
			{
				if(args[k] == ">" || args[k] == ">>" || args[k] == "<" || args[k] == "|")
				{
					redircmd(args, firstcmd, piper);	//goes to execute redirect or pipe command
					rdir = true;
				}
			}
			
			
			if(rdir)	//if first command is a redirector
			{
				if(firstcmd == false)	//if first command is not executed
				{		//skip next command if first command isn't executed
					for(;str[i]; i++)
					{
						if(str[i+1] == ";" || str[i+1] == "||" || str[i+1] == "&&")
						{
							break;
						}
					}
				}
				rdir = false;  //reset rdir
				firstcmd = false; // reset first cmd
				//execute next command
			}
			else		//if first command is not a redirector
			{
                       		if(execvp(args[0],args) == -1)//execute whatever args is	//becomes first command
                        	{
                                	perror("there's an error on && execvp.");//error checking
                                	exit(1);
                      		}
				else 
				{
					firstcmd = true;
				}	

				if(firstcmd == false)	//if first command is not exacutable, skip next command
				{
					for(;str[i]; i++)
					{
						if(str[i+1] == ";" || str[i+1] == "||" || str[i+1] == "&&")
						{
							break;
						}
					}
				}
				//execute next command
				firstcmd = false; // reset first cmd
			}
						
			delete[] args;		//reset args
			args = new char*[50];
			j = 0;
				
		}
		else if(strcmp(str[i], "||") == 0)    //"||": use second if first false
                {
			args[j] == '\0';

			if(args[0] == "cd" || args[0] == "ls" || args[0] == "cp" || args[0] == "cat" || args[0] == "echo") // checks command arguments
			{
				checkcmd(args);
			}

			for(int k = 0; args[k]; k++)	//checks if args is redirect or pipe
			{
				if(args[k] == ">" || args[k] == ">>" || args[k] == "<" || args[k] == "|")
				{
					redircmd(args, firstcmd, piper);	//goes to execute redirect or pipe command
					rdir = true;
				}
			}

			if(rdir)	//if first command is a redirector
			{
				if(firstcmd)	//if first command is  executed
				{		//skip next command if first command isn't executed
					for(;str[i]; i++)
					{
						if(str[i+1] == ";" || str[i+1] == "||" || str[i+1] == "&&")
						{
							break;
						}
					}
					firstcmd = false; // reset first cmd
				}
				rdir = false; //reset rdir
				
				//execute next command
			}
			else		//if first command is not a redirector
			{
                       		if(execvp(args[0],args) == -1)//execute whatever args is	//becomes first command
                        	{
                                	perror("there's an error on || execvp.");//error checking
                                	exit(1);
                      		}
				else 
				{
					firstcmd = true;
				}	

				if(firstcmd)	//if first command is exacutable, skip next command
				{
					for(;str[i]; i++)
					{
						if(str[i+1] == ";" || str[i+1] == "||" || str[i+1] == "&&")
						{
							break;
						}
					}
					firstcmd = false; // reset first cmd
				}
				//execute next command
			}
						
			delete[] args;			//reset args
			args = new char*[50];
			j = 0;
                }
                else{           //assign argument with string at i
                        args[j] = str[i];
			j++;
                }
		
        }
        args[j] = '\0';	//if goes through to end of string
	
	if(args[0] == "cd" || args[0] == "ls" || args[0] == "cp" || args[0] == "cat" || args[0] == "echo") // checks command arguments
	{
		checkcmd(args);
	}

	for(int k = 0; args[k]; k++)	//checks if args is redirect or pipe
	{
		if(args[k] == ">" || args[k] == ">>" || args[k] == "<" || args[k] == "|")
		{
			redircmd(args, firstcmd, piper);	//goes to execute redirect or pipe command
			rdir = true;
		}
	}

	if(rdir)	//if args is a redirected command
	{
		rdir = false;	// reset rdir
	}
	else		// if args is not a redirected command
	{
		if(execvp(args[0],args) == -1)//execute whatever args is
                {
                	perror("there's an error on execvp.");//error checking
                        exit(1);
                }
	}
	firstcmd = false;		
	delete[] args;	//reset args
	args = new char*[50];
	j = 0;

        return;
}

#endif
