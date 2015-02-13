#include <fstream>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include "Timer.h"

using namespace std;

void getput(const string src, string dst);
void rwchar(string src, string dst);
void rwbuff(string src, string dst);

int main() {
	
	string srcfile;
	cout << "enter source file: " << flush;
	cin >> srcfile;
	cout << endl;
	
	string dstfile;
	cout << "enter destination file: " << flush;
	cin >> dstfile;
	cout << endl;
	
	string choice;
	cout << "which function?: ";
	cin >> choice;
	cout << endl;

	if(choice == "1") getput(srcfile, dstfile);
	else if (choice == "2") rwchar(srcfile, dstfile);
	else if (choice == "3") rwbuff(srcfile, dstfile);
	else {
		cout << "invalid choice of function." << endl;
	}
}

void getput(const string src, string dst){
	//opening file to read
	ifstream is;
	is.open(src.c_str());
	//error checking input
	if(!is.is_open()) {
		cerr << "problem opening input file" << endl;
		exit(EXIT_FAILURE);
	}
	
	//opening output file
	ofstream outfile;
	outfile.open(dst.c_str());
	//error checking output
	if(!outfile.is_open()) {
		cerr << "problem opening output file" << endl;
		exit(EXIT_FAILURE);
	}	
	
	char c;
	
	while (!is.eof()){
		is.get(c);
		outfile.put(c);
	};
	
	is.close();
	outfile.close();
	return;
}

void rwchar(string src, string dst) {
	//opening file to read
	int fd_src = open(src.c_str(), O_RDONLY);
	if (fd_src == -1) {
		perror ("open src file");
	}
	
	int fd_dst = open(dst.c_str(), O_WRONLY | O_CREAT);
	
	if(fd_dst == -1) {
		perror("open dst file");
	}
	
	int buffersize = 1;
	char buf[buffersize];
	int ret;
	do{
		ret = read(fd_src, buf, buffersize);
		if(ret == -1) {
			perror("read");
		}
			
		if(-1 == write(fd_dst, buf, ret)) {
			perror("write");
		}
	}while(ret != 0);
	
	close(fd_src);
	close(fd_dst);
	
	return;
}
	
void rwbuff(string src, string dst) {

	return;
}	
