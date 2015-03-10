#ifndef CMDLEXEC_H	//looks for cd, ls, and cp commands
#define CMDLEXEC_H	//executes redirection ( >, >>, <, and |)
			//returns true if process can be executed
#include <unistd.h>
#include <string.h>	//need to:
#include <stdio.h>	
			//complete executions of >>
#include "cp.h"
#include "pipe.h"
#include "execute.h"
#include "cmdLexec.h"

using namespace std;

void redircmd(char** a, bool& bg, bool &firstc, bool pip)
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
			char** dest;
			dest = new char*[50];
			int k = 0;
			for(;a[p]; p++)
			{
				dest[k] = a[p];
				k++;
			}
			dest[k] = '\0';

			if(strcmp(execute[0], "0") == 0 || 
				strcmp(execute[0], "1") == 0 || 
				strcmp(execute[0], "2") == 0)
			{
				char* conv = (char*)malloc(1);
				int hold = 0;
				for(int k = 0;a[k]; k++)
				{
					for(int l = 0; a[k][l]; l++)
					{
						conv[hold] = a[k][l];
						hold++;
					}
				}
				if(strcmp(execute[0], "0") == 0) //input
				{
					int fd = 0;
				        if (fd == -1)
        				{
                				perror("open src file");
        				}
					
					int ofd = open(conv, O_WRONLY | O_CREAT | O_EXCL);
        				if(ofd == -1)
        				{
                				perror("open dst file");
        				}

        				char buf[BUFSIZ];

        				int bytes_read = read(fd, buf, BUFSIZ);
        				if(bytes_read == -1)
        				{
                				perror("read");
        				}

        				int bytes_written = write(ofd, buf, bytes_read);
        				if(bytes_written == -1)
        				{
                				perror("write");
        				}

        				if(-1 == close(ofd)) perror("close dest");
		
				}
				else if(strcmp(execute[0], "1") == 0) //output 
				{
					int fd = 1;
					int ofd = open(conv, O_WRONLY |O_CREAT | O_EXCL);
					if(ofd == -1)
					{
						perror("open dst file");
					}
					char buf[BUFSIZ];
					int b_read = read(fd, buf, BUFSIZ);
					if(b_read == -1){
						perror("read");
					}
					int b_write = write(ofd, buf, b_read);
					if(b_write == -1)
					{
						perror("write");
					}
					if(close(ofd) == -1) perror("close dest");
						
				}
				else if(strcmp(execute[0], "2") == 0)//error
				{
					int fd = 2;
					int ofd = open(conv, O_WRONLY |O_CREAT | O_EXCL);
					if(ofd == -1)
					{
						perror("open dst file");
					}
					char buf[BUFSIZ];
					int b_read = read(fd, buf, BUFSIZ);
					if(b_read == -1){
						perror("read");
					}
					int b_write = write(ofd, buf, b_read);
					if(b_write == -1)
					{
						perror("write");
					}
					if(close(ofd) == -1) perror("close dest");
				}			
			}
			cprwbuf(execute, dest);
				
			// else if a file or directory
			//else say if it is a command 
 		}
        	else if(strcmp(a[p], "<") == 0) //accept input from file on right
	        {//uses int ec
			execute[e] = '\0';
			char** dest;
			dest = new char*[50];
			int k = 0;
			for(;a[p]; p++)
			{
				dest[k] = a[p];
				k++;
			}
			dest[k] = '\0';

			if(strcmp(execute[0], "0") == 0 || 
				strcmp(execute[0], "1") == 0 || 
				strcmp(execute[0], "2") == 0)
			{
				char* conv = (char*)malloc(1);
				int hold = 0;
				for(int k = 0;a[k]; k++)
				{
					for(int l = 0; a[k][l]; l++)
					{
						conv[hold] = a[k][l];
						hold++;
					}
				}
				if(strcmp(execute[0], "0") == 0) //input 
				{
					int fd = 0;
				        if (fd == -1)
        				{
                				perror("open src file");
        				}
					
					int ofd = open(conv, O_WRONLY | O_CREAT | O_EXCL);
        				if(ofd == -1)
        				{
                				perror("open dst file");
        				}

        				char buf[BUFSIZ];

        				int bytes_read = read(ofd, buf, BUFSIZ);

        				if(bytes_read == -1)
        				{
                				perror("read");
        				}

        				int bytes_written = write(fd, buf, bytes_read);
        				if(bytes_written == -1)
        				{
                				perror("write");
        				}

        				if(-1 == close(ofd)) perror("close dest");		
				}
				else if(strcmp(execute[0], "1") == 0) //output 
				{
					int fd = 1;
					int ofd = open(conv, O_WRONLY |O_CREAT | O_EXCL);
					if(ofd == -1)
					{
						perror("open dst file");
					}
					char buf[BUFSIZ];
					int b_read = read(ofd, buf, BUFSIZ);
					if(b_read == -1){
						perror("read");
					}
					int b_write = write(fd, buf, b_read);
					if(b_write == -1)
					{
						perror("write");
					}
					if(close(ofd) == -1) perror("close dest");
					
				}
				else if(strcmp(execute[0], "2") == 0)//error
				{
					int fd = 2;
					int ofd = open(conv, O_WRONLY |O_CREAT | O_EXCL);
					if(ofd == -1)
					{
						perror("open dst file");
					}
					char buf[BUFSIZ];
					int b_read = read(ofd, buf, BUFSIZ);
					if(b_read == -1){
						perror("read");
					}
					int b_write = write(fd, buf, b_read);
					if(b_write == -1)
					{
						perror("write");
					}
					if(close(ofd) == -1) perror("close dest");
					
				}
			}
			cprwbuf(dest, execute);
				
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
			
			pipexec(execute, bg, scndprt, pip);

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
		if(execvp(a[0], a) == -1)
		{
			perror("error in ls exec");
		}
	}
	else if(strcmp(a[0], "mv") == 0)
	{
		//move 	
	}
	else if(strcmp(a[0], "rm") == 0)
	{
		//remove 
	}
	else if(strcmp(a[0], "cp") == 0)	//check if command is cp
	{
		if(Asize == 2)
		{
			char* rep[] = {a[1],'\0'};
			char* rep2[] = {a[0],'\0'};

			cprwbuf(rep, rep2);	
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
