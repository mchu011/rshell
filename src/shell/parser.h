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

void addspace(string &s)	//add spaces before and after connectors
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

void parseCmd(bool& a, char clist[], char* res) //parse command to tokenize
{
	char* tokenlist;
	tokenlist = strtok(clist, " \t\n"); //FIXME segfault here

	while(tokenlist != NULL)
	{
		if(a)	//if string is empty, then break the tokenizing
		{
			break;
		}	
		
		tokenlist = strtok(NULL, " \t\n");
	}
	res = tokenlist;
	return;
}

#endif

