#ifndef EXECUTE_H
#define EXECUTE_H

#include <unistd.h>	//executes via fork
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "redirect.h"// might be the dup in pipe.h

void myexec(bool &first, char** a)
{
	int execute;
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
		if(strstr(a,">") != NULL || 	//if execution is redirect
			strstr(a, "<") != NULL ||
			strstr(a, ">>") != NULL)
		{
			redir(first, a);//go to redirection execution
		}
		else
		{
  	              if((execute = execvp(a[0], a)) == -1) //execute argurments
			{
				perror("myexec cvp");
			}
			if(!errno)
			{
				first = true;
			}
		}
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
