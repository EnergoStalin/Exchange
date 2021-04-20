#include <bitset>
#include <iostream>
#include <algorithm>
#include <string>

std::string to_bin(int i)
{
	std::string bin;
	bin += std::to_string(i & 1);
	while((i = i >> 1) != 0)
	{
		bin += std::to_string(i & 1);
	}
	std::string rev(bin.rbegin(),bin.rend());

	return rev;
}

int main(int argc, char const *argv[])
{
	size_t count = 0;

	for (size_t i = 7; i <= 56; i++)
	{
		std::string bin = to_bin(i);
		bin.resize(6,'0');

		size_t one = std::count_if(bin.begin(),bin.end(), [&count](char s) { return s == '1'; });

		if(one == 3) count++;
	}

	std::cout << count << '\n';

	return 0;
}