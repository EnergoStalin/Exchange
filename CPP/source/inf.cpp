#define SIZE 20

#include <iostream>
#include "Arrays.cpp"

using namespace ArrayTools;

int main(int argc, char **argv)
{
	int a[SIZE];
	int min = 1000, j = 0;

	FillIntArray(a,SIZE);

	for(int i = 0; i < SIZE; i++)
	{
		if((a[i] % 2 == 0) && (a[i] > 0) && (a[i] <= min))
		{
			min = a[i];
			j++;
		}
	}
	std::cout << min << '\t' << j << '\n';

	return 0;
}
