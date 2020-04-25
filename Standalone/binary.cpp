#include <iostream>
#include <bitset>

#define flip(x) (((x) == 0) ? 0 : (~(x) + 1))
#define abs(x) ((((x) & 64) == 64) ? flip(x) : (x))

int main(int argc, char const *argv[])
{
	int a = -145; //int 64 bit
	int b = abs(a); //binary abs
	int c = flip(0b010010001); //binary flip

	std::cout << "int\n";
	std::cout << std::bitset<sizeof(a)*16>(a) << '\t' << a << '\n';
	std::cout << std::bitset<sizeof(a)*16>(b) << '\t' << b << '\n';
	std::cout << std::bitset<sizeof(a)*16>(c) << '\t' << c << '\n';

	unsigned int aa = abs(-150);
	std::cout << std::bitset<sizeof(aa)*16>(aa) << '\t' << aa << '\n';
	unsigned short int aaa = abs(-300);
	std::cout << "unsigned short int\n";
	//dont use abs macro for this types use flip instead
	std::cout << std::bitset<sizeof(aaa)*16>(aaa) << '\t' << aaa << '\n';
	unsigned long int aaaa = flip(-3523);
	std::cout << "unsigned long int\n";
	std::cout << std::bitset<sizeof(aaaa)*16>(aaaa) << '\t' << aaaa << '\n';
	unsigned long long int aaaaa = flip(-1353);
	std::cout << "unsigned long long int\n";
	std::cout << std::bitset<sizeof(aaaaa)*16>(aaaaa) << '\t' << aaaaa << '\n';
	unsigned long long aaaaaa = flip(-3533);
	std::cout << "unsigned long long\n";
	std::cout << std::bitset<sizeof(aaaaaa)*16>(aaaaaa) << '\t' << aaaaaa << '\n';
	long long cc = flip(aaaaaa);
	std::cout << "long long\n";
	std::cout << std::bitset<sizeof(cc)*16>(cc) << '\t' << cc << '\n';
	long long int ccc = flip(aaaaa);
	std::cout << "long long int\n";
	std::cout << std::bitset<sizeof(ccc)*16>(ccc) << '\t' << ccc << '\n';
	short int cccc = flip(aaaa);
	std::cout << "short int\n";
	std::cout << std::bitset<sizeof(cccc)*16>(cccc) << '\t' << cccc << '\n';

	return 0;
}