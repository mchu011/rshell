#ifndef PARSER_H		//used to parse for comments and connectors
#define PARSER_H

#include <stdio.h>	//fix parsing tokens
#include <unistd.h>	//get tokens to work
#include <stdlib.h>	
#include <iostream> 		
#include <string.h>
#include <vector>
#include <cstdlib>
#include <cstdio>

using namespace std;

void addspace(string &s)
{
	int sz = s.size();
	
	for(int i = 0; i < sz; i++)
	{
		if(s[i] == ';')	//for connector ';'
		{
			if(s[i-1] != ' ' || s[i+1] != ' ')
			{
				if(s[i-1] != ' ' && s[i+1] != ' ')
				{
					s.insert(i+1, " ");
					s.insert(i, " ");
				}
				else if(s[i-1] != ' ' && i != 0)
				{
					s.insert(i, " ");
				}
				else if(s[i+1] != ' ')
				{
					s.insert(i+1, " ");
				}
			}
		}
		else if(s[i] == '#')//for comments
		{
			s[i] = '\0';
			break;
		}
		else if(s[i] == '&')	//for connector '&&'
		{
			if(s[i+1] == '&')
			{
				if(s[i-1] != ' ' || s[i+2] != ' ')
				{
					if(s[i-1] != ' ' && s[i+2] != ' ')
					{
						s.insert(i+1, " ");
						s.insert(i, " ");
					}
					else if(s[i-1] != ' ' && i != 0)
					{
						s.insert(i, " ");
					}
					else if(s[i+2] != ' ')
					{
						s.insert(i+1, " ");
					}
				}
			}
		}
		else if(s[i] == '|')	//for connector '||'
		{
			if(s[i+1] == '|')
			{
				if(s[i-1] != ' ' || s[i+2] != ' ')
				{
					if(s[i-1] != ' ' && s[i+2] != ' ')
					{
						s.insert(i+1, " ");
						s.insert(i, " ");
					}
					else if(s[i-1] != ' ' && i != 0)
					{
						s.insert(i, " ");
					}
					else if(s[i+2] != ' ')
					{
						s.insert(i+1, " ");
					}
				}
			}
		}
	}
}

/*
char** parseCmd(string s)	FIXME	//parser to separate commands and connectors to tokens
{
	char** tokenlist;
	tokenlist[0] = strtok(clist, " "); //get the first token
	for(int i = 1; clist[i];i++)
	{
		tokenlist[i] = strtok(NULL, " "); //get the rest of token
	}
	//delete[] clist; //do not include this

	for(int p = 0; tokenlist[p]; p++)
	{
		cout << tokenlist[p] << endl;
	}
	
	return  tokenlist;	
}*/


#endif

