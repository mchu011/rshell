#ifndef PARSER_H		//used to parse for comments and connectors
#define PARSER_H

#include <stdio.h>	
#include <unistd.h>	
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
					s.insert(i+1, " ");//insert after&before
					s.insert(i, " ");
				}
				else if(s[i-1] != ' ' && i != 0)
				{
					s.insert(i, " ");//insert before
				}
				else if(s[i+1] != ' ')
				{
					s.insert(i+1, " ");//insert after
				}
			}
		}
		else if(s[i] == '#') //for comments '#'
		{
			s[i] = '\0';	//replace with null
			break;
		}
		else if(s[i] == '&')	//for connector '&&'
		{
			if(s[i+1] == '&')//if next char is '&'
			{
				if(s[i-1] != ' ' || s[i+2] != ' ')
				{
					if(s[i-1] != ' ' && s[i+2] != ' ')
					{
						s.insert(i+2, " ");//insert after
						s.insert(i, " ");	//& before
					}
					else if(s[i-1] != ' ' && i != 0)
					{
						s.insert(i, " ");//insert before
					}
					else if(s[i+2] != ' ')
					{
						s.insert(i+2, " ");//insert after
					}
				}
			}
		}
		else if(s[i] == '|')	//for connector '||'
		{
			if(s[i+1] == '|') //if next char is '|'
			{
				if(s[i-1] != ' ' || s[i+2] != ' ')
				{
					if(s[i-1] != ' ' && s[i+2] != ' ')
					{
						s.insert(i+2, " ");//insert after
						s.insert(i, " ");// & before
					}
					else if(s[i-1] != ' ' && i != 0)
					{
						s.insert(i, " ");
					}
					else if(s[i+2] != ' ')
					{
						s.insert(i+2, " ");
					}
				}
			}
		}
	}
}

void parseCmd(char clist[], char** res) //parse command to tokenize
{
	int cntsz = 0;	//array position for res
	char* tokenlist;
	tokenlist = strtok(clist, " \t\n"); //tok only returns char*
	
	while(tokenlist != NULL)
	{
		res[cntsz] = tokenlist; //save tokenlist into res 
		cntsz++;
		tokenlist = strtok(NULL, " \t\n");
	}
	res[cntsz] = '\0';//null at end of string
	return;
}

#endif

