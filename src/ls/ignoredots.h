#ifndef IGNOREDOTS_H
#define IGNOREDOTS_H

#include<vector>	//takes out all files that
#include<string.h>	//start with '.'

using namespace std;

vector<string> takeoutdots(vector<string> s)
{
	char* check;
	vector<string> newstr;
	for(unsigned k = 0; k < s.size(); k++)
	{
		check = (char*)s[k].c_str();
		
		if(check[0] !=  '.')//takes out files
		{		//with dots in the front		
			newstr.push_back(s.at(k));
		}				
			
	}		
	return newstr; 
}

#endif
