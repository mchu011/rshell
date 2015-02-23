#ifndef CP_H
#define CP_H

#include <fstream>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/stat.h>

using namespace std;

void cprwbuf(char** in, char** out) {
	char* inner;
	int hold = 0;
	for(int d = 0; in[d] ; d++)
	{
		for(int q = 0; in[d][q]; q++)
		{
			inner[hold] = in[d][q];
			hold++;
		}
	}
	char* outer;
	hold = 0;
	for(int d = 0; out[d]; d++)
	{
		for(int q = 0; out[d][q]; q++)
		{	
			outer[hold] = out[d][q];
			hold++;
		}
	}

     	int fd = open(inner, O_RDONLY);
	if (fd == -1)
        {
		perror("open src file");
	}

 	int ofd = open(outer, O_WRONLY | O_CREAT | O_EXCL);
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
	
        if(-1 == close(fd)) perror("close src");
	if(-1 == close(ofd)) perror("close dest");

	return;
}	
#endif
