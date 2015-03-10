#ifndef COLFORMAT_H
#define COLFORMAT_H

#include <dirent.h> //need to get better format output 
#include <vector>	
#include <string.h>
#include <stdio.h>
#include <sys/ioctl.h>
			
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
	for(;dirfiles[totit] != "\0";totit++) //get total number of items
	{
		charsz += sizeof(dirfiles[totit]); //for finding column splits
		charsz +=2;
	}
	
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);

	int scnsz = w.ws_col - 5; //screen size with indents
	int rows;
	
	if(charsz%scnsz == 0)
	{
		rows = charsz/scnsz; //gets number of rows needed
	}
	else
	{
		int so = scnsz/2;
		if((charsz%scnsz) > so)
		{
			int hold = charsz;
			rows = hold/scnsz;
			while((hold%scnsz) > so)
			{
				rows++;
				hold -=scnsz;
			}
			rows++;
		}
		else
		{	
			rows= (charsz/scnsz)+1;
		}
	}

	if(rows == 1) // if just one row
	{
		for(int i = 0; i < totit; i++)
		{
			cout << left << dirfiles[i] << flush;
			cout << "  " <<flush;
		}	
		
		cout << endl;
	}
	else	// if more than one row
	{ 
		int newcol;
		if(totit%rows != 0)	//get number of columns
		{
			newcol = (totit/rows)+1; //if odd
		}
		else	//if even
		{
			newcol = (totit/rows);
		}
		
		vector<unsigned int> mxcol;//get max column size
	
		for(int c = 0; c < newcol; c++)
		{
			mxcol.push_back(0);
		}
	
		vector<string> cols;

		int item = 0;		//into column array and get max column size
		for(int r = 0; r < rows && item < totit; r++)
		{
			for(int c = 0; c < newcol && (r+(rows*c)) < totit; c++)
			{
				cols.push_back(dirfiles[r+(rows*c)]);
				
				string see = dirfiles[r+(rows*c)];//check string sz
				char* str = (char*)see.c_str();
				unsigned int strsz = 0;
				for(;str[strsz];strsz++){}
	
				item++;
				if(mxcol[c] < strsz)
				{
					mxcol[c] = strsz;
				}
			}
			cols.push_back("\0");
		}
		
		item = 0;
		int rcnt = 0;
		for(int r = 0; r < rows && item < totit; r++)
		{
			for(int c = 0; c < newcol; c++)
			{
				string s = cols[item];
				char* str = (char*)s.c_str();//size of current str
				int stsz = 0;
				for(;str[stsz];stsz++){}
	
				rcnt += stsz;
				int space = mxcol[c] - stsz;
				if(w.ws_col < (rcnt+2+space))
				{
					cout << endl;
					rcnt = stsz;
					cout << cols[item] << flush;
				}
				else
				{
					cout << cols[item] << flush;
					if(space > 0)
					{
						for(int sp = 0; sp < space; sp++)
						{
							cout << " " <<flush;
							rcnt++;
						}
					}
					rcnt+=2;
					cout << "  " << flush;
				}
				item++;
			}
			item++;
			rcnt = 0;
			if(r+1 < rows)
			{
				cout << endl;
			}
		}
	}
	closedir(directory);	
	//find width, height, and tab size here	

	return;
}

#endif
