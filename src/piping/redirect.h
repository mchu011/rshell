#ifndef REDIRECT_H
#define REDIRECT_H

void redir(bool& first, char** ex)
{

	for(int k = 0; ex[k]; k++)
	{
		if(strcmp(ex[k], ">") == 0)
		{
			
		}
		else if(strcmp(ex[k], "<") == 0)
		{
			
		}
		else if(strcmp(ex[k], ">>") == 0)
		{
			
		}
	}
	return;
}

#endif
