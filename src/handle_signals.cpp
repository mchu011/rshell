#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <csignal>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <cstdlib>

using namespace std;



int cntC = 0;
int cntSlash = 0;
int cntZ = 0;


void sigHandle(int signum)
{
	if(signum == SIGINT)
	{
		cout << " c " << flush;
		cntC++;
	}
	else if(signum == SIGQUIT)
	{
		cout << " \\ " << flush;
		cntSlash++;
	}
	else if(signum == SIGTSTP)
	{
		cout << " s " << flush;
		cntZ++;
		int pid = getpid();
		kill(pid, SIGSTOP);
		SIGCONT;
	}
	return;
}

int main()
{	
	while(1)
	{
		if(cntZ == 3)
		{
			break;
		}
		cout << "x " << flush;
		
		if(signal(SIGINT, sigHandle) == SIG_ERR)
		{
			perror("main sigint");
			exit(1);
		}
		if(signal(SIGQUIT, sigHandle) == SIG_ERR)
		{
			perror("main sigquit");
			exit(1);
		}
		if(signal(SIGTSTP, sigHandle) == SIG_ERR)
		{
			perror("main sigtstp");
			exit(1);
		}
	
		sleep(1);
		cout << endl;
	}
	cout << endl;
	cout << "^c: " << cntC << endl;
	cout << "^\\: " << cntSlash << endl;
	cout << "^z: " << cntZ << endl;
	return 0;
}
