#ifndef EXECUTE_H
#define EXECUTE_H

#include <unistd.h>	//executes via fork
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "cd.h"
#include "ls.h"
#include "mvrm.h"
#include "cp.h"
#include "exit.h"

void myexec(bool &first, char** a)
{
	int status;
	int child; 
	child = fork(); //fork
        if(child == -1)
        {
              	perror("there's an error with fork().");
                exit(1);
        }
        else if(child == 0)     //child function
        {
		//signal(SIGINT, NULL);

		//signal(SIGTSTP, NULL);
		if(strcmp(a[0], "exit") == 0)
		{	
			exitcode(a[0]);    //checks if command is exit
		}
		else if(strcmp(a[0], "ls") == 0)//execute arguments
		{ 
			lscode(a); //run ls
		}
		else if(strcmp(a[0], "mv") == 0 || //run rm and mv
			strcmp(a[0], "rm") == 0 ||
			strcmp(a[0], "rmdir") == 0)
		{
			mvrm(a);	
		}
		else if(strcmp(a[0], "cp") == 0)
		{
			int sz = 0;
			for(;a[sz];sz++) {}
			if(sz == 2)
			{
				char* rep[] = {a[1],'\0'};
	                        char* rep2[] = {a[0],'\0'};

				cprwbuf(rep, rep2);
			}
			else
			{
				cout << "too many arguments" <<endl;
				return;
			}
			//run cp
		}
		else if(strcmp(a[0], "cd") == 0) // run cd
		{
			cdpath(a);
		}
		else if(strcmp(a[0], "cat") == 0)
		{
			//run cat
		}
		else if(strcmp(a[0], "echo") == 0)
		{
			//run echo
			string s = "";
			for(int j = 1; a[j]; j++)
			{
				s+=a[j];
				s+=" ";
			}
			cout << s << endl;
			
		}
       		/*if((execute = execvp(a[0], a)) == -1)
		{
			perror("myexec cvp");
		}*/
		if(errno == 0)
		{
			first = true;
		}
		sleep(1);
                exit(0);
        }
        else            //parent function
        {
                if(waitpid(child, &status, 0) == -1)//wait and perror
                {
                        perror("there's an error with wait().");
                }
        }
	
	
	return;
}

#endif
