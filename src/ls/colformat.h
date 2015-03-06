#ifndef COLFORMAT_H
#define COLFORMAT_H

#include <dirent.h> //need to 
#include <vector>	//double check includes
#include <string.h>	//look up column formats
			//needs better column format
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
	/*if(ig)
	{
		dirfiles = takeoutdots(dirfiles);
	}*/
	dirfiles.push_back("\0");

	int i = 0;

	//find width, height, and tab size here	

	while(dirfiles[i] != "\0")
	{
		if(dirfiles[i] == "\0")
		{
			break;
		}
		struct stat sfiles;
		char filepath[1024];
		strcpy(filepath, dirName);
		strcat(filepath, "/");
		strcat(filepath, dirfiles[i].c_str());

		if((stat(filepath, &sfiles)) == -1)
		{
			perror("there's an issue with stat prinl");
		}

		int size = 0;
		if((stat(filepath, &sfiles)) == -1)
		{
			perror("there's an issue with stat prinl");
		}

		if(dirfiles[i][0] == '.')
		{
			//add /
			//dirfiles[i] += '/'
		}
		
		if(ig) //if dots need to be taken out
		{
			if(dirfiles[i][0] == '.')
			{
				//skip dots		
			}
			else
			{
				if(i != 0)
				{
					cout <<"\t" << flush;
					cout << dirfiles[i] << flush;
					//printlfcolor(sfiles,dirtpoint);
				}
				else
				{
					cout << dirfiles[i] << flush;
					//printlfcolor(sfiles,dirtpoint);
				}
			}
		}
		else
		{
			if(i != 0)
			{
				cout <<"\t" << flush;
				cout << dirfiles[i] << flush;
				//printlfcolor(sfiles,dirtpoint);
			}
			else
			{
				cout << dirfiles[i] << flush;
				//printlfcolor(sfiles,dirtpoint);
			}
		}
		i++;
	}
	/*string blak = "";
	int wSz = 0;

	for(unsigned i = 0; i < tab.at(0).size(); i++)
	{
		for( unsigned j = 0; j < tab.size(); j++)
		{
			struct stat x;
			if(i < tab.at(j).size())
			{
				blak = dNm + "/";
				blak += tab[j][i];
				
				if(stat((char*)blak.c_str(), &x) == -1)
				{
					perror("thare's a problem in printcol stat");
					exit(1);
				}
				
				if(x.st_mode & S_IRWXU & S_IXUSR)
				{
					printf("\033[1;32m");
				}
				
				if(S_ISDIR(x.st_mode))
				{
					printf("\033[1;34m");
				}
				wSz = w[j] + 2;
				std::cout << std::left << std::setw(wSz) 
					<< tab[j][i] << std::flush;
				printf("\033[0m");
			}
		}
		wSz = 0;
		if(i < tab[0].size() -1)
		{
			printf("\n");
		}
	}*/
	return;
}

#endif
