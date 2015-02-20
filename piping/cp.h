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

void cprwbuf(string in, string out) {
     	int fd = open(in.c_str(), O_RDONLY);
	if (fd == -1)
        {
		perror("open src file");
	}

 	int ofd = open(out.c_str(), O_WRONLY | O_CREAT | O_EXCL);
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
