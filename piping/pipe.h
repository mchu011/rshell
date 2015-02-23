#ifndef PIPE_H
#define PIPE_H

void pipexec(char** a, char** b, bool &c)
{
	int filedir[2];
	if(pipe(filedir) == -1)
	{
		perror("there's a problem with pipe");
	}

	int pipepid = fork();
	if(pipepid == -1)
	{
		perror("pipepid fork");
	}
	else if(pipepid == 0)
	{
		dupit(a);
		
		if(dup2(filedir[1],1) == -1)
		{
			perror("there's a problem in dup2 1");
		}
		if(close(filedir[0]) == -1)
		{
			perror("there's a problem in close");
		}
		
		if(execvp(a[0], a) == -1)
		{
			perror("there's a proplem in pipe child exec");
		}
		exit(1);
	}
	else
		int savestdin;
		if((savestdin = dup(0)) == -1)
		{
			perror("ther's a problem with savestdin dup");
		}
		if(wait(0) == -1)
		{
			perror("there's a problem with wait");
		}
		

		int pid2 = fork();
		if(pid2 == -1)
		{
			perror("pid2 fork");
		}
		else if(pid2 == 0)
		{
			if(dup2(filedir[0], 0) == -1)
			{
				perror("ther's aproblem in dup2 pid2");
			}
			if(close(filedir[1]) == -1)
			{
				perror( "there's a problem with close pid2");
			}
			
			if(execvp(b[0], b) == -1)
			{
				perror("ther's a probem in pipe2 child exec");
			}
			
			exit(1);
		}
		else
		{
			if(wait(0) == -1)
			{
				perror("ther's a problem with pid2 wait");
			}
		}
	}
	if(dup2(savestdin) == -1)
	{
		perror("ther's a problem with dup2 savstdin");
	}
	return;
}

#endif
