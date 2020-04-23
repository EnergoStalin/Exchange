#include <iostream>
#include <cstring>

int main(int argc,char **argv)
{
	if(!argv[1])
	{
		std::cout << "No arg passed try help for more info.\n";
		return 1;
	}
	if(strcmp(argv[1],"int") == 0) std::cout << sizeof(int) << '\n';
	else if(strcmp(argv[1],"char") == 0) std::cout << sizeof(char) << '\n';
	else if(strcmp(argv[1],"bool") == 0) std::cout << sizeof(bool) << '\n';
	else if(strcmp(argv[1],"float") == 0) std::cout << sizeof(float) << '\n';
	else if(strcmp(argv[1],"double") == 0) std::cout << sizeof(double) << '\n';
	else if(strcmp(argv[1],"-h") == 0)
	{
		std::cout << "Sizeof v1.0 made ";
		std::cout << "by EnergoStalin.\n";
		std::cout << "Display this page -";
		std::cout << " '-h'\n";
		std::cout << "Avalible data types:\n";
		std::cout << "int\nchar\nbool\nfloat\ndouble\n";
		std::cout << "Free for use and exploit.)\n";
	}
	else { std::cout << "Undefined type or option try -h to get some help.\n"; return 1; }


	return 0;
}

