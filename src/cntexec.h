#ifndef CNTEXEC_H			
#define CNTEXEC_H			//distinguishes separate commands from connectors

#include <unistd.h>			//has issues with "&&" and "||" 			
#include <stdio.h>
#include <string.h>			

#include "execute.h"
#include "exit.h"
#include "cd.h"
#include "cp.h"
#include "ls.h"
#include "mvrm.h"

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
			if(strcmp(args[0], "exit") == 0)
			{	
				exitcode(args[0]);    //checks if command is exit
			}
			else if(strcmp(args[0], "ls") == 0)
			{
				//runls(args); //run ls
				lscode(args);
			}
			else if(strcmp(args[0], "cd") == 0)
			{
				cdpath(args);
			}
			else if(strcmp(args[0], "mv") == 0 || 
				strcmp(args[0], "rm") == 0 ||
				strcmp(args[0], "rmdir") == 0)
			{
				mvrm(args);	
			}
			else if(strcmp(args[0], "cp") == 0)
			{
				int sz = 0;
				for(;args[sz];sz++) {}
				if(sz == 2)
				{
					char** rep;
					rep[0] = args[1];
					rep[1] = '\0';
					char** rep2;
					rep2[0] = args[0];
					rep2[1] = '\0';
					cprwbuf(rep, rep2);
				}
				else
				{
					cout << "too many arguments" <<endl;
					return;
				}
				//run cp
			}
			else if(strcmp(args[0], "cat") == 0)
			{
				//run cat
			}
			else if(strcmp(args[0], "echo") == 0)
			{
				//run echo
				string s = "";
				for(int j = 1; args[j]; j++)
				{
					s+=args[j];
					s+=" ";
				}
				cout << s << endl;
				
			}
			else
			{
				myexec(firstcmd, args);
			}
			
			delete[] args;	        //reset args
			
			args = new char*[50];
			j = 0;
			firstcmd = false;
                }	
                /*else if(strcmp(str[i], "&&") == 0)  // "&&": execute second if first true
		{
			args[j] = '\0';	
			if(strstr(args[0], "exit") != NULL)
			{
				exitcode(args[0]);	     //checks if command is exit
			}			

			myexec(firstcmd, args);

			if(firstcmd == false)	//if first command is not exacutable, skip next command
			{
				for(;str[i]; i++)
				{
					if(strcmp(str[i+1],";") == 0 || 
						strcmp(str[i+1],"||") == 0 || 
						strcmp(str[i+1], "&&") == 0)
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
		else if(strcmp(str[i], "||") == 0)    //"||": use second if first false
                {
		
			args[j] = '\0';
			if(strstr(args[0], "exit") != NULL)  //FIXME segfalut here
			{
				exitcode(args[0]); //checks if command is exit
			}
			
			myexec(firstcmd, args);
			
			if(firstcmd)	//if first command is executable, skip next command
			{
				firstcmd = false; // reset first cmd
				for(;str[i]; i++)
				{
					if(strcmp(str[i+1], ";") == NULL || 
						strcmp(str[i+1], "||") == NULL || 
						strcmp(str[i+1], "&&") == NULL)
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
                }*/
		i++;	
        }
	args[j] = '\0';//reaches to final command/end of string
	
	if(strstr(args[0], "exit") != NULL)
	{
		exitcode(args[0]);	//check if command is exit
	}
	else if(strcmp(args[0], "ls") == 0)
	{
		//lscode(args);
	}
	else if(strcmp(args[0], "cd") == 0)
	{
		cdpath(args);
	}
	else if(strcmp(args[0], "mv") == 0 || 
		strcmp(args[0], "rm") == 0 ||
		strcmp(args[0], "rmdir") == 0)
	{
		mvrm(args);	
	}
	else if(strcmp(args[0], "cp") == 0)
	{
		int sz = 0;
		for(;args[sz];sz++) {}
		if(sz == 2)
		{
			char** rep;
			rep[0] = args[1];
			rep[1] = '\0';
			char** rep2;
			rep2[0] = args[0];
			rep2[1] = '\0';
			cprwbuf(rep, rep2);
		}
		else
		{
			cout << "too many arguments" <<endl;
			return;
		}
		//run cp
	}
	else if(strcmp(args[0], "cat") == 0)
	{
		//run cat
	}
	else if(strcmp(args[0], "echo") == 0)
	{
		//run echo
		string s = "";
		for(int j = 1; args[j]; j++)
		{
			s+=args[j];
			s+=" ";
		}
		cout << s << endl;
	}
	else
	{
		myexec(firstcmd, args);
	}

	firstcmd = false;// reset first cmd
	delete[] args;	//deallocate args

        return;
}

#endif
