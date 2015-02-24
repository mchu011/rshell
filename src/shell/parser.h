#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
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

void exitcode(char* k)		//if string is "exit", close program
{
	if(strcmp(k, "exit") == 0)
	{
		exit(1);
	}
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



/*void init_info(parseInfo *p)
{
	#initialize parse info struct
}

void parse_command(char*command, struct commandType *comm)
{
	#parse a single command
}

parseInfo *parse (char *cmdline) #parse commandline for space separated commands
{
	#for each command in commandline
	{
		if(cmd == command)
		{
			parse_command(cmd, type);
		}
	}
}

void print_info (parseInfo *info)
{
	#for each type in parseinfo
	{
		#print "type_name: type"
	}
}

void free_info (parseInfo *info)
{
	#for each memory block in parseInfo
	{
		free(memory_block)
	}
}*/
#endif

