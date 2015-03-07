#ifndef GETHOSTNAME_H
#define GETHOSTNAME_H

#include <unistd.h> 
#include <cstdlib>
#include <pwd.h>
#include <string.h> 
#include <vector>

using namespace std;

void gethnm(char* h)
{
	if(gethostname(h, 25) == -1)    //get hostname
        {
                perror("There's a problem in gethostname");
                exit(1);
        }

        /*for(int i = 0; h[i]; i++)
        {
                if(h[i] = '.')
                {
                        h[i] = '\0';
                }
        }*/
	return;
}

#endif
