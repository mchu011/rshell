#ifndef SIGNALS_H
#define SIGNALS_H

#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

using namespace std;

void sigc(int signum)//should not exit but go to forground
{
	if(signum == SIGINT)
	{
		//signal(SIGINT, sigc);
		//cout << endl;
		//exit(0);
		//int pid; 
		//getpid(pid, pid);
		//kill(pid, SIGKILL);
		signal(SIGINT, SIG_IGN);	
		//goes to foreground
		//returns to main.cpp			
	}
	return;
}

void sigz(int signum)//pause and implement fg and bg
{
	if(signum == SIGTSTP)
	{
		//int pid;
		//getpid(pid, pid); //error here
		kill(0, SIGCONT); //need alternate pause
		//SIGCONT;	//need fg and bg
		//returns to main.cpp 
	}
}

#endif
