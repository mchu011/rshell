#ifndef CNTEXEC_H			
#define CNTEXEC_H			//distinguishes separate commands from connectors

#include <unistd.h>			//has issues with && and || 			
#include <stdio.h>
#include <string.h>			

#include "execute.h"
#include "exit.h"

using namespace std;

void cnctexec(char** str){		//first copy execution list into local
					//list to determine execution
	char** args;	
        args = new char*[50];//allocate separate new char** for single commands
	
	bool firstcmd = false;//for && and ||	
	int i = 0;
        int j = 0;

        while(str[i] != NULL)       //parse through char pointer array for connectors
        {
                if(strcmp(str[i],";") == 0)	//';' execute and continue
                {
			args[j] = '\0';
			if(strstr(args[0], "exit") != NULL)
			{	
				exitcode(args[0]);    //checks if command is exit
			}
			
			myexec(firstcmd, args);
			
			delete[] args;	        //reset args
			
			args = new char*[50];
			j = 0;
			firstcmd = false;
                }	
                /*else if(strcmp(str[i], "&&") == 0)  // "&&": execute second if first true FIXME
		{
			args[j] = '\0';	
			if(strstr(args[0], "exit") != NULL)
			{
				exitcode(args[0]);	     //checks if command is exit
			}			

			myexec(firstcmd, args);

			if(firstcmd == false)	//if first command is not executable
			{			//skip next command
				for(;str[i]; i++)
				{
					if(strstr(str[i+1],";") != NULL || 
						strstr(str[i+1],"||") != NULL || 
						strstr(str[i+1], "&&") != NULL ||
						strcmp(str[i+1], '\0') == 0)
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
			if(strstr(args[0], "exit") != NULL)  //segfalut here
			{
				exitcode(args[0]); //checks if command is exit
			}
			
			myexec(firstcmd, args);
			
			if(firstcmd)	//if first command is executable, skip next command
			{
				firstcmd = false; // reset first cmd
				for(;str[i]; i++)
				{
					if(strstr(str[i+1], ";") != NULL || 
						strstr(str[i+1], "||") != NULL || 
						strstr(str[i+1], "&&") != NULL ||
						strcmp(str[i+1], '\0') == 0)
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

	myexec(firstcmd, args);

	firstcmd = false;// reset first cmd
	delete[] args;	//deallocate args

        return;
}

#endif
