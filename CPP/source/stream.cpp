#include <iostream>

int str2len(const char *str)
{
int i = 0;
while(str[i] != '\0')
i++;

return i;
}

bool equals(const char *str1, const char *str2)
{
if(str2len(str1) != str2len(str2)) return false;
for(int i = 0; i < strlen(str1); i++)
if(str1[i] != str2[i]) return false;

return true;
}

int main(int argc, char **argv)
{
char buff;
while(std::cin.get(buff))
{
std::cout << buff;
}

return 0;
}