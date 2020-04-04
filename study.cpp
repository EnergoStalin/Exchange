#include <iostream>
//#include "Arrays.cpp"
//#define DEBUG
#include "arg.cpp"

//using namespace ArrayTools;

int main(int argc, char **argv) {
	Arg arg(argc,argv);
	char *parse = arg.find("--parse");
	char *sep = arg.find("--sep");
	char *start_with = arg.find("--from");
	if(parse && sep)
	{
		int start_with_i = 0;
		if(start_with && is_digit(start_with))
		{
			start_with_i = atoi(start_with);
		}
		else
		{
			std::cout << "Warning: \"" << start_with << "\" Don't digit passed as 0.\n";
		}
		int len = len4str(parse);
		if(start_with_i < 0 || start_with_i > len)
		{
			std::cout << "Warning: Invalid option --from: Exception out of bounds " << start_with_i << '/' << len << " passed as 0.\n";
			start_with_i = 0;
		}
		char *obj = getObject(start_with_i,parse,*sep);
		if(obj)
		{
			std::cout << obj << '\n';
		}
		else
		{
			std::cout << "Cant parse string.\n";
		}
		delete []obj;
	}
	else
	{
		std::cout << "Please input --parse --sep and --from option.\n";
	}

	return 0;
}