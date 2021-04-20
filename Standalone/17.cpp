#include <iostream>
#include <cstdlib>

void Help()
{
	std::cout << "Usage:\nprogramm min:int max:int divs:int\n";
}

bool isParam(const char *c)
{
    char* p;
    strtol(c, &p, 10);
    return *p == 0;
}

int main(int argc, char const *argv[])
{
	if(argc < 4)
	{
		Help();
		return 1;
	}

	if(!(isParam(argv[1]) && isParam(argv[2]) && isParam(argv[3])))
	{
		std::cout << "Invalid input.\n";
		Help();
		return 1;
	}

	int beg = atoi(argv[1]);
	int end = atoi(argv[2]);
	int divs = atoi(argv[3]);
	

	std::cout << "Min: " << beg << "\tMax: " << end << "\tDivs: " << divs << '\n';


	int count = 0;
	int min = end;
	for (int i = beg; i <= end; ++i)
	{
		size_t delims = 0;
		for (int k = 1; k <= i && (delims < (divs+1)); ++k)
		{
			if(i % k == 0)
			{
				delims++;
			}
		}

		if(delims > divs)
		{
			count++;
			if(min > i) min = i;
		}
	}

	std::cout << "Count: " << count << "\tMin: " << min << '\n';
	
	return 0;
}