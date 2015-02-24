#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>	//fix parsing tokens
#include <unistd.h>
#include <stdlib.h>
#include <iostream> 		//still need to edit with shell file
#include <string.h>

char* cmtout(char* c)	//find comments and comment them out
{
	int counter;
	for(int i = 0; c[i] != '\0'; i++)
	{
		counter++;
	}
	counter++;

	for(int j = 0; j < counter; j++)
	{
		if(c[j] == '#')
		{
			c[j] == '\0';
		}
	}

	return c;
}

char** parseCmd(std::string s)		//parser to separate commands and connectors to tokens
{
	char* c = (char*)s.c_str();
	char* clist;
	int k = 0;
	int j = 0;
	
	for(j; c[j]; j++)	//for no space between connectors
	{
		if(c[j] == ';')
		{
			if (c[j-1] != ' ')
			{
				clist[j+k] = ' ';
				k++;
			}
			
			clist[j+k] = c[j];
			k++;
			if(c[j+1] != ' ')
			{
				clist[j+k] = ' ';
				k++;
			}	
		}
		else if(c[j] == '&')
		{
			if(c[j+1] == '&')
			{
				if(c[j-1] != ' ')
				{
					c[j+k] = ' ';
					k++;
				}	
				clist[j+k] = c[j];
				j++;
				clist[j+k] = c[j];
				k++;
				if(c[j+1] !=  ' ')
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
		else if(c[j] == '|')
		{
			if(c[j+1] == '|')
			{
				if(c[j-1] != ' ')
				{
					clist[j+k] = ' ';
					k++;
				}
				clist[j+k] = c[j];
				j++;
				clist[j+k] = c[j];
				k++;
				if(c[j+1] != ' ')
				{
					clist[j+k] = ' ';
					k++;
				}
			}
		}
		else
		{
			clist[j+k] = c[j];
		}
	}
	clist[j+k] = '\0';	
	
	char** tokenlist;
	tokenlist[0] = strtok(clist, " ");
	for(int i = 1; clist[i];i++)
	{
		tokenlist[i] = strtok(NULL, " ");
	}
	
	return  tokenlist;	
}


#endif

