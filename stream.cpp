#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

/*int strlen(const char *str);
//count string lenth

bool equals(const char *str1, const char *str2);
//Check string for equal another string require strlen function
*/
int main(int argc, char **argv)
{
	for(const auto &entry : fs::directory_iterator("./"))
	{
		std::cout << entry.path() << '\n';
	}

	return 0;
}
/*
int strlen(const char *str)
{
	int i = 0;
	while(str[i] != '\0')
		i++;

	return i;
}

bool equals(const char *str1, const char *str2)
{
	if(strlen(str1) != strlen(str2)) return false;
	for(int i = 0; i < strlen(str1); i++)
		if(str1[i] != str2[i]) return false;

	return true;
}
*/