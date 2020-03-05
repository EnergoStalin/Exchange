#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>

//#define DEBUG

typedef unsigned short int usi;

char digits[] = {'0','1','2','3','4','5','6','7','8','9'};

int strlen(const char *str)
{
	int i = 0;
	while(str[i] != '\0')
	{
		i++;
	}
	#ifdef DEBUG
		std::cout << "String '" << str << "' length " << i << ".\n";
	#endif //Debug
	return i;
}

bool is_int(const char *str)
{
	if(str[0] == digits[0]) return false;
	for(usi i = 0; i < strlen(str); i++)
	{
		bool drop = true;
		for(usi j = 0; j < 10; j++)
		{
			if(str[i] == digits[j])
			{
				#ifdef DEBUG
					std::cout << "Is digit - " << str[i] << '\n';
				#endif //Debug
				drop = false;
				break;
			}
		}
		if(drop) return false;
	}
	return true;
}

bool CompareString(const char *str1, const char *str2)
{
	int len = strlen(str1);

	if(len != strlen(str2)) return false;

	for(int i = 0; i < len; i++)
	{
		if(str1[i] != str2[i]) return false;
	}

	return true;
}

int main(int argc, char **argv)
{
	srand((unsigned)time(0));
	switch(argc)
	{
		case 1:
			std::cout << rand() << '\n';
		break;
		case 2:
			if(!is_int(argv[1])) { std::cout << "Dont integer count passed. Terminating...\n"; return 1; }
			for(usi i = 0; i < atoi(argv[1]); i++)
			{
				std::cout << rand() << '\n';
			}
		break;
		case 3:
			if(!is_int(argv[2])) { std::cout << "Dont integer seed passed. Terminating...\n"; return 1; }
			if(CompareString(argv[1],"-seed")) srand((unsigned)atoi(argv[2]));
			std::cout << rand() << '\n';
		break;
		case 4:
			if(!is_int(argv[2])) { std::cout << "Dont integer seed passed. Terminating...\n"; return 1; }
			if(!is_int(argv[3])) { std::cout << "Dont integer count passed. Terminating...\n"; return 1; }
			if(atoi(argv[3]) > USHRT_MAX)
			{
				std::cout << "Value out of range. Max value is " << USHRT_MAX << ".\n";
				return 1;
			}
			if(CompareString(argv[1],"-seed") || CompareString(argv[1],"seed")) srand((unsigned)atoi(argv[2]));
			for(usi i = 0; i < atoi(argv[3]); i++)
			{
				std::cout << rand() << '\n';
			}
		break;
		default:
			std::cout << "Unknown arguments.\n";
		break;
	}

	return 0;
}
