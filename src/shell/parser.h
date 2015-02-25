#ifndef PARSER_H		//used to parse for comments and connectors
#define PARSER_H

#include <stdio.h>	//fix parsing tokens
#include <unistd.h>	
#include <stdlib.h>
#include <iostream> 		//still need to edit with shell file
#include <string.h>

using namespace std;

char** parseCmd(string s)		//parser to separate commands and connectors to tokens
{
	char* c = (char*)s.c_str();
	char* clist = new char[100];
	int k = 0;
	int j = 0;
	
	for(j; c[j]; j++)	//for no space between connectors until NULL
	{
		if(c[j] == '#') //if character is a comment
		{
			break;
		}
		else if(c[j] == ';')	//if character is ';'
		{
			if (c[j-1] != ' ') //if there is no space before ';'
			{
				clist[j+k] = ' ';
				k++;
			}
			clist[j+k] = c[j];
			k++;
			if(c[j+1] != ' ') //if there is no space after ';'
			{
				clist[j+k] = ' ';
				k++;
			}	
		}
		else if(c[j] == '&') //for '&'
		{
			if(c[j+1] == '&')//if there is another '&'
			{
				if(c[j-1] != ' ') //add spaces before
				{
					c[j+k] = ' ';
					k++;
				}	
				clist[j+k] = c[j];//save '&&' to list
				j++;
				clist[j+k] = c[j];
				k++;
				if(c[j+1] !=  ' ')//add space after
				{
					clist[j+k] = ' ';
					k++;
				}
			}
			else
			{
				clist[j+k] = c[j];
				k++;
			}
		}
		else if(c[j] == '|') //for '||'
		{
			if(c[j+1] == '|')
			{
				if(c[j-1] != ' ') //add spaces before
				{
					clist[j+k] = ' ';
					k++;
				}
				clist[j+k] = c[j];//save '||'
				j++;
				clist[j+k] = c[j];
				k++;
				if(c[j+1] != ' ') //add space after
				{
					clist[j+k] = ' ';
					k++;
				}
			}
			else
			{
				clist[j+k] = c[j];
				k++;
			}
		}
		else{		//pass regular char into clist
			clist[j+k] = c[j];
		}
	}
	clist[j+k] = '\0';	//end of clist line
	
	char** tokenlist;
	tokenlist[0] = strtok(clist, "  \t\n");//token until space, tab, or newline
	for(int i = 1; clist[i];i++)
	{
		tokenlist[i] = strtok(NULL, "  \t\n");
	}
	delete[] clist;
	
	return  tokenlist;	
}


#endif

