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

int cntC = 0;		//counters
int cntSlash = 0;
int cntZ = 0;


void sigHandle(int signum)	//signal handler
{
	if(signum == SIGINT)	//for ctrl+c
	{
		cout << " c " << flush;
		cntC++;
	}
	else if(signum == SIGQUIT)	//for ctrl + \
	{
		cout << " \\ " << flush;
		cntSlash++;
	}
	else if(signum == SIGTSTP)	//for cotrl +z
	{
		cout << " s " << flush;
		cntZ++;
		int pid = getpid();	//get pid
		kill(pid, SIGSTOP);	//stop program
		SIGCONT;		//resume program
	}
	return;
}

int main()
{	
	while(1)
	{
		if(cntZ == 3)//stop when ctrl+z is pressed thrice
		{
			break;
		}
		cout << "x " << flush;
		
		if(signal(SIGINT, sigHandle) == SIG_ERR)//error check ctrl +c
		{
			perror("main sigint");
			exit(1);
		}
		if(signal(SIGQUIT, sigHandle) == SIG_ERR)//error check ctrl+\
		{
			perror("main sigquit");
			exit(1);
		}
		if(signal(SIGTSTP, sigHandle) == SIG_ERR)//error check ctrl+z
		{
			perror("main sigtstp");
			exit(1);
		}
	
		sleep(1);//pause for 1 sec
		cout << endl;
	}
	cout << endl;		//output count results
	cout << "^c: " << cntC << endl;
	cout << "^\\: " << cntSlash << endl;
	cout << "^z: " << cntZ << endl;
	return 0;
}
