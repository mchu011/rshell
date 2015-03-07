#ifndef PATH_H
#define PATH_H

void pathcng()
{
	char* newPath = getenv("PATH");
	if(newPath != NULL)
	{
		printf("new path is %s", newPath);
	}
}

#endif
