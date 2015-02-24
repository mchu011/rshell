#ifndef PARSER_H			//parses for commands
#define PARSER_H			//executes 'exit' command
					//keeps out comments (#) in command
#include <stdio.h>			//separates connectors (; || &&)
#include <unistd.h>			//and commands (> >> < |) into tokens
#include <stdlib.h>
#include <iostream> 	
#include <string.h>

using namespace std;

char* cmtout(char* c)	//find comments and comment them out
{
	int counter;
	for(int i = 0; c[i] != '\0'; i++)	//counts how long string is
	{
		counter++;
	}
	counter++;

	for(int j = 0; j < counter; j++)	//parses for comment (#)
	{			
		if(c[j] == '#')		//replaces comment with NULL
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

int parseCmd(string s, char** cl, bool empty)//parser to separate commands and connectors to tokens
{
	if(empty)	//return if empty string
	{
		return 0;
	}
	int counter = 0;	
	char* c = (char*)s.c_str();	//gets string from main code
	char* clist;
	int k = 0;
	int j = 0;
	
	for(j; c[j]; j++){	//for no space between connectors

		if(c[j] == ';'){		//for connector ';'

			if (c[j-1] != ' '){	//if at end/middle of word
				clist[j+k] = ' ';
				k++;
			}

			clist[j+k] = c[j];
			k++;

			if(c[j+1] != ' '){	//if at beginning/middle of word
				clist[j+k] = ' ';
				k++;
			}	
		}
		else if(c[j] == '&'){		//for connector '&&'
		
			if(c[j+1] == '&'){	//checks for second char
				if(c[j-1] != ' '){	//separates '&&'
					c[j+k] = ' ';	//into single word
					k++;		//before tokening
				}	
				clist[j+k] = c[j];
				j++;
				clist[j+k] = c[j];
				k++;
				if(c[j+1] !=  ' '){
					clist[j+k] = ' ';
					k++;
				}
			}
			else	{		//if no second char
						// leave as is since no idea
				clist[j+k] = c[j];	//what to do 
				k++;			//with just '&'
			}				//NOTE modify later
		}
		else if(c[j] == '|'){	//for connector '||' and pipe '|'
		
			if(c[j+1] == '|'){	//for connector '||'
			
				if(c[j-1] != ' '){	//separates '||' 
					clist[j+k] = ' ';	// into word
					k++;
				}
				clist[j+k] = c[j];
				j++;
				clist[j+k] = c[j];
				k++;
				if(c[j+1] != ' '){
					clist[j+k] = ' ';
					k++;
				}
			}
			else{			//separates '|' into word
				if(c[j-1] != ' '){
					clist[j+k] = ' ';
					k++;
				}
				clist[j+k] = c[j];
				j++;
				clist[j+k] = c[j];
				k++;
				if(c[j+1] != ' '){
					clist[j+k] = ' ';
					k++;
				}
			}
		}
		else if(c[j] == '<'){	//for command '<'
		
			if (c[j-1] != ' '){	//separates '<' into word
				clist[j+k] = ' ';
				k++;
			}
			clist[j+k] = c[j];
			k++;
			if(c[j+1] != ' '){
				clist[j+k] = ' ';
				k++;
			}	
		}
		else if(c[j] == '>'){ 	//for commands '>>' and '>'
			if(c[j+1] == '>'){	//for '>>'
				if(c[j-1] != ' '){	//separates '>>'
					clist[j+k] = ' ';	//into word
					k++;
				}
				clist[j+k] = c[j];
				j++;
				clist[j+k] = c[j];
				k++;
				if(c[j+1] != ' '){
					clist[j+k] = ' ';
					k++;
				}
			}
			else{		//separtates '>' into word
				if(c[j-1] != ' '){
					clist[j+k] = ' ';
					k++;
				}
				clist[j+k] = c[j];
				j++;
				clist[j+k] = c[j];
				k++;
				if(c[j+1] != ' '){
					clist[j+k] = ' ';
					k++;
				}
			}
		}	
		else{		//if just a normal character
			clist[j+k] = c[j];
		}
	}
	clist[j+k] = '\0';	//add null to end of list
	
	char** tokenlist;		//make tokenlist
	tokenlist[0] = strtok(clist, " \t\n");
	for(int i = 1; clist[i];i++)
	{
		tokenlist[i] = strtok(NULL, " \t\n");
		counter++;
	}
	
	cl = tokenlist;	
	return counter;
}


#endif
