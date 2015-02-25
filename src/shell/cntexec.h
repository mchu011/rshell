#ifndef CNTEXEC_H			
#define CNTEXEC_H			//distinguishes separate commands from connectors
					
#include <unistd.h>			
#include <stdio.h>
#include <string.h>			//need to fix execution error

#include "exit.h"

using namespace std;

void cnctexec(char** str){		//first copy execution list into local
					//list to determine execution
        char** args;	
        args = new char*[50];
	
	bool firstcmd = false;	
	int i = 0;
        int j = 0;
	int execute;
        for(;str[i]; i++)       //parse through char pointer array for connectors
        {
                if(str[i] == ";")	//';' execute and continue
                {				
			exitcode(args);    //checks if command is exit
			
                       	if((execute = execvp(args[0],args)) == -1)   //execute whatever args is
                        {
                        	perror("there's an error on ; execvp.");   //error checking
                                exit(1);
                      	}

			delete[] args;	        //reset args
			args = new char*[50];
			j = 0;

                }	
                else if(str[i] == "&&")  // "&&": execute second if first true
		{	
			exitcode(args);	     //checks if command is exit			

                       	if((execute = execvp(args[0],args)) == -1)    //execute whatever args is & becomes first command
                        {
                                perror("there's an error on && execvp.");//error checking
                                exit(1);
                      	}
			else if(execute == 0) 
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
			delete[] args;		//reset args
			args = new char*[50];
			j = 0;
				
		}
		else if(str[i] == "||")    //"||": use second if first false
                {
			exitcode(args); //checks if command is exit
			
                       	if((execute = execvp(args[0],args)) == -1)//execute whatever args is	//becomes first command
                       	{
                               	perror("there's an error on || execvp.");//error checking
                               	exit(1);
                     	}
			else if(execute == 0)
			{
				firstcmd = true;
			}	

			if(firstcmd)	//if first command is exacutable, skip next command
			{
				firstcmd = false; // reset first cmd
				for(;str[i]; i++)
				{
					if(str[i+1] == ";" || str[i+1] == "||" || str[i+1] == "&&")
					{
						break;
					}
				}
			}
				//execute next command
						
			delete[] args;			//reset args
			args = new char*[50];
			j = 0;
                }
                else{           //assign argument with string at i
                        args[j] = str[i];
			j++;
                }
		
        }
	exitcode(args);

	if(execvp(args[0],args) == -1)//execute whatever args is
        {
        	perror("there's an error on execvp.");//error checking
                exit(1);
        }

	firstcmd = false;// reset first cmd
	delete[] args;	//deallocate args

        return;
}

#endif
