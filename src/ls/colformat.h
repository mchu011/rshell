#ifndef COLFORMAT_H
#define COLFORMAT_H

#include <dirent.h> //need to get better format output 
#include <vector>	
#include <string.h>
			
using namespace std;

void printcol(bool &ig)
{
	char* dirName =(char*)"."; //this is to get current directory
	DIR* directory;
	directory = opendir(dirName);
	dirent *dirtpoint;
	vector<string> dirfiles;
	
	if(!(directory = opendir(dirName)))
	{
		perror("Error with col opendir");
	}
		
	while((dirtpoint = readdir(directory))) //save dirctory names
	{
		if(errno != 0)
		{
			perror("there's a problem in read dir");
			exit(1);
		}

		dirfiles.push_back(dirtpoint->d_name);//gets filename
	}

	sort(dirfiles.begin(), dirfiles.end(),locale("en_US.UTF-8"));//sorts files

	if(ig) //takes out dot files
	{
		dirfiles = takeoutdots(dirfiles);
	}
	dirfiles.push_back("\0");

	int totit = 0;
	int charsz = 0;
	for(;dirfiles[totit] != "\0";totit++) //get total number to display
	{
		charsz += sizeof(dirfiles[totit]); //for estimating colnumbers
	}
	int numcol = 0;
	int avgsz = 0;
	
	avgsz = charsz/totit;//gets average size of strings

	numcol = 60/avgsz; //gets number of columns

	int rows = 0;
	rows = totit/numcol; //finds the number of rows needed
	int* mxcol; //get max column size for each column
	
	for(int c = 0; c < numcol; c++)
	{
		mxcol[c] = 0;
	}
	
	for(int k = 0; k < numcol; k++) 
	{
		for(int p = 0;(p*rows) < totit; p++)
		{
			int s = p*rows;
			int sz = sizeof(dirfiles[s]);
			if(sz > mxcol[k]) //segfault here fixme
			{
				mxcol[k] = sz;
			}
		}
	}
	
	int rcnt = 0;
	for(int k = 0; k < rows; k++) //print files
	{
		for(int p = 0;((p*rows) < totit) && (rcnt < rows); p++)
		{
			struct stat sfiles;
			char filepath[1024];
			strcpy(filepath, dirName);
			strcat(filepath, "/");
			strcat(filepath, dirfiles[p*rows].c_str());
			cout << left << dirfiles[p*rows] << flush;
			
			int space = mxcol[k] - sizeof(dirfiles[p*rows]);
			
			if(space > 0)
			{
				for(int q = 0; q < space; q++)
				{
					cout << " " << flush;
				}
			}
			cout << "  " << flush;
		}
		if(rcnt >= rows)
		{
			break;
		}
	}
	




	/*vector<string>* cols; //sort into columns
	
	int mrow = 0;
	int j;
	for(int k = 0; k < numcol; k++)//puts directory into columns
	{
		for(j = 0; (j < rows) && dirfiles[mrow] != "\0"; j++)
		{
			cols[k][j] = dirfiles[mrow];//FIXME segfaults here
			mrow++;	
			cout << cols[k][j] << endl;
		}	
		cols[k][j].push_back('\0');
	}

	for(int c = 0; c < rows; c++)
	{
		for(int d = 0; cols[d][c] != "\0"; d++)
		{
			if(sizeof(cols[d][c]) > mxcol[d])
			{
				mxcol[d] = sizeof(cols[d][c]);
			}
		}
	}
	
	for(int c = 0; c < rows; c++)//outputs into column rows
	{
		for(int d = 0; cols[d][c] != "\0"; d++)
		{
			struct stat sfiles;
			char filepath[1024];
			strcpy(filepath, dirName);
			strcat(filepath, "/");
			strcat(filepath, cols[d][c].c_str());

			cout <<cols[d][c] << flush;
			int space = mxcol[d] -sizeof(cols[d][c]);
			
			for(int k = 0; k < space; k++)
			{
				cout << " " << flush;
			}
			cout << "\t" << flush;
		}
		cout << endl;
	}*/

	//must always have five columns
	//find width, height, and tab size here	

	return;
}

#endif
