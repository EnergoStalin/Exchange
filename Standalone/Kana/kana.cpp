#include <iostream>
#include <cmath>
#include <string>
#include <vector>


std::vector < std::string > results;
int tests, dragon_health, lighting_amount, absorb_amount;
std::string fight();
void lighting();
void absorb();

int main()
{
	std::cin >> tests;
	for (int i = 0; i < tests; i++)
	{
		std::cin >> dragon_health >> absorb_amount >> lighting_amount;
		#ifdef DEBUG
			std::cout << "Simulating battle" << i << ".\n\tKana vs Dragon\n";
		#endif
		results.push_back(fight());
	}
	
	for(auto i = results.begin(); i != results.end(); i++)
		std::cout << *i << '\n';


	return 0;
}

void lighting()
{
	
	dragon_health -= 10;
	lighting_amount--;
	#ifdef DEBUG
		std::cout << "Kana kast lighting:\n";
		std::cout << "\tDragon health " << dragon_health << '\n';
		std::cout << "\tLighting amount " << lighting_amount << '\n';
	#endif
}

void absorb()
{
	dragon_health = floor(dragon_health / 2) + 10;
	absorb_amount--;
	#ifdef DEBUG
		std::cout << "Kana cast void absorb:\n";
		std::cout << "\tDragon health " << dragon_health << '\n';
		std::cout << "\tAbsorb amount " << absorb_amount << '\n';
	#endif
}

int make_choice()
{
	if(absorb_amount != 0 && ((dragon_health - lighting_amount * 10) > 0))
	{
		return 1;
	}
	else if(lighting_amount != 0)
	{
		return 2;
	}
	
	return -1;
}

std::string fight()
{
	while ((lighting_amount != 0 || absorb_amount != 0) && dragon_health > 0)
	{
		switch (make_choice())
		{
			case 1:
			{
				absorb();
				break;
			}
			case 2:
			{
				lighting();
				break;
			}
			default: { break; }
		}
	}

	if (dragon_health <= 0)
	#if defined(DEBUG)
		return "Win";
	#else
		return "YES";
	#endif
	else
	#if defined(DEBUG)
		return "Loose";
	#else
		return "NO";
	#endif
}
