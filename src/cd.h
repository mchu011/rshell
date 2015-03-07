#ifndef CD_H
#define CD_H

void cdpath(char** cdstr)
{
	int cnt = 0;
	for(int q = 0; cdstr[q]; q++)
	{
		cnt++;
	}
	
	if(cnt == 2)
	{
		string path = cdstr[1];
		char *curdir = (char*) ".";
		
		link(curdir, path.c_str());
		
	}
	else if(cnt == 1)
	{
		char* gohome = getenv("HOME");
		if(chdir(gohome) == -1)
		{
			perror("error in chdir home");
		}
	}
	else
	{
		perror("too many arguments");
	}
	return;
}

#endif
