#ifndef COLFORMAT_H
#define COLFORMAT_H

void printCol(vector <vector<char*> > tab, vector<int> w, string dNm)
{
	string blak = "";
	int wSz = 0;

	for(unsigned i = 0; i < tab.at(0).size(); i++)
	{
		for( unsigned j = 0; j < tab.size(); j++)
		{
			struct stat x;
			if(i < tab.at(j).size())
			{
				blak = dNm + "/";
				blak += tab[j][i];
				
				if(stat((char*)blak.c_str(), &x) == -1)
				{
					perror("thare's a problem in printcol stat");
					exit(1);
				}
				
				if(x.st_mode & S_IRWXU & S_IXUSR)
				{
					printf("\033[1;32m");
				}
				
				if(S_ISDIR(x.st_mode))
				{
					printf("\033[1;34m");
				}
				wSz = w[j] + 2;
				std::cout << std::left << std::setw(wSz) 
					<< tab[j][i] << std::flush;
				printf("\033[0m");
			}
		}
		wSz = 0;
		if(i < tab[0].size() -1)
		{
			printf("\n");
		}
	}
}

#endif
