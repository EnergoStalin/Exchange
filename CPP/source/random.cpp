#include <iostream>
#include <cstdlib>
#include <ctime>

int main(int argc, char **argv)
{
srand((unsigned)time(0));
switch(argc)
{
case 1:
std::cout << rand() << '\n';
break;
case 2:
for(unsigned short int i = 0; i <= atoi(argv[1]); i++)
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
