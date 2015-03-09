#ifndef BACKGROUND_H
#define BACKGROUND_H


bool bgd(int a, char** arg)
{
	bool bckg = false;
	if(strcmp(arg[a], "&&") == 0 ||
		strcmp(arg[a], "||") == 0 || 
		strcmp(arg[a], "|") == 0)	
	{
		bckg = true;
		arg[a] = NULL;
	}
	else
	{
		int len = strlen(arg[a]) -1;
		char* cpy = arg[len];
		if(strcmp(cpy, "&&") == 0 ||
			strcmp(cpy, "||") == 0 ||
			strcmp(cpy, "|") == 0)
		{
			bckg = true;
			cpy = NULL;
			arg[len] = cpy;
		}
	}
	return bckg;
}


#endif
