#ifndef CNTEXEC_H			
#define CNTEXEC_H			//distinguishes separate commands from connectors
					//and executes either pipe or regular
#include <unistd.h>			//has issues with && and || 			
#include <stdio.h>
#include <string.h>			

#include "execute.h"
#include "pipe.h"
#include "cmdLexec.h"
#include "background.h"
#include "exit.h"

using namespace std;

void cnctexec(char** str, bool bkgrd, char **pPath){	//first copy execution list into local
					//list to determine execution
	char** args;	
        args = new char*[50];//allocate separate new char** for single commands
	
	bool firstcmd = false;//for && and ||	
	int i = 0;
        int j = 0;
	bool rdir = false;
        while(str[i] != NULL)       //parse through char pointer array for connectors
        {
                if(strcmp(str[i],";") == 0)	//';' execute and continue
                {
			args[j] = '\0';
			if(strstr(args[0], "exit") != NULL)
			{	
				exitcode(args[0]);    //checks if command is exit
			}
			
			for(int k = 0; args[k]; k++)
			{
				if(strstr(args[k], "|") != NULL)
				{
					pipexec(args, bkgrd, pPath, firstcmd); //execute pipe
					rdir = true;
				}
			}
			
			if(rdir == false)
			{
				myexec(firstcmd, args); //regular execution
			}
			
			delete[] args;	        //reset args
			
			args = new char*[50];
			j = 0;
			firstcmd = false;
			rdir = false;
                }	
               /* else if(strcmp(str[i], "&&") == 0)  // "&&": execute second if first true FIXME
		{
			args[j] = '\0';	
			if(strstr(args[0], "exit") != NULL)
			{
				exitcode(args[0]);	     //checks if command is exit
			}			
			else if(strstr(args, "|") != NULL)
			{
				pipexec(args, bkgrd, pPath, firstcmd); //execute pipe
			}
			else
			{
				myexec(firstcmd, args); //regular execution
			}

			if(firstcmd == false)	//if first command is not executable
			{			//skip second command
				for(;str[i]; i++)
				{
					if(strstr(str[i+1],";") != NULL || 
						strstr(str[i+1],"||") != NULL || 
						strstr(str[i+1], "&&") != NULL)
					{
						break;
					}
				}
			}
			
			firstcmd = false; // reset first cmd			
			delete[] args;		//reset args
			args = new char*[50];
			j = 0;
		}
		else if(strcmp(str[i], "||") == 0)    //"||": use second if first false FIXME
                {
		
			args[j] = '\0';
			if(strstr(args[0], "exit") != NULL) 
			{
				exitcode(args[0]); //checks if command is exit
			}
			else if(strstr(args, "|") != NULL)
			{
				pipexec(args, bkgrd, pPath, firstcmd); //execute pipe
			}
			else
			{
				myexec(firstcmd, args);//regular execution
			}
			
			if(firstcmd)	//if first command is executable, skip next command
			{
				firstcmd = false; // reset first cmd
				for(;str[i]; i++)
				{
					if(strstr(str[i+1], ";") != NULL || 
						strstr(str[i+1], "||") != NULL || 
						strstr(str[i+1], "&&") != NULL)
					{
						break;
					}
				}
			}
				//execute next command
						
			delete[] args;			//reset args
			args = new char*[50];
			j = 0;
                }*/
                else{           //assign argument with string at i
                        args[j] = str[i];
			j++;
                }	
		i++;
        }
	args[j] = '\0';//reaches to final command/end of string
	
	if(strstr(args[0], "exit") != NULL)
	{
		exitcode(args[0]);	//check if command is exit
	}
	for(int k = 0; args[k]; k++)
	{
		if(strstr(args[k], "|") != NULL)
		{
			pipexec(args, bkgrd, pPath, firstcmd); //execute pipe
			rdir = true;
		}
	}

	if(rdir == false)
	{
		myexec(firstcmd, args); //regular execution
	}

	rdir = false;
	firstcmd = false;// reset first cmd
	delete[] args;	//deallocate args

        return;
}

#endif
