#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <ctime>

enum AppControlCode
{
	EVT_EXIT = 0x000001
} AppControlCode;

struct AppConfig
{
	AppConfig() {}
	AppConfig(std::string n1, std::string n2, float max = 100, int at = 1) : nickname1(n1), nickname2(n2), count_attempts(at), max(max) {}
	std::string nickname1 = "Player1";
	std::string nickname2 = "Player2";
	size_t count_attempts = 1;
	float max = 100;
	
} AppConfig;

struct HEntry
{
	HEntry() {}
	HEntry(float p1,float p2, float r) : p1(p1), p2(p2), r(r) {}
	float p1 = 0;
	float p2 = 0;
	float r = 0;
};

struct AppState
{
	float a = 0, b = 0;
	bool run = true;
	std::vector<HEntry> history;
} AppState;

void getInput(float &ref, std::string hellomsg = "", std::string errmsg = "")
{
	do
	{
		if(std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(99999,'\n');
			std::cerr << errmsg;
		}
		std::cout << hellomsg;
		std::cin >> ref;
	}
	while(std::cin.fail());
}

int main(int argc, const char **argv)
{
	srand((unsigned)time(NULL));

	try
	{
		while(true)
		{
			getInput(
				AppState.a,
				"[" + AppConfig.nickname1 + "] Input: ",
				"\n[" + AppConfig.nickname1 + "] ERROR WHILE INPUT\n"
			);
			
			if(AppState.a == -1) throw EVT_EXIT;
			
			getInput(
				AppState.b,
				"[" + AppConfig.nickname2 + "] Input: ",
				"\n[" + AppConfig.nickname2 + "] ERROR WHILE INPUT\n"
			);
			
			if(AppState.b == -1) throw EVT_EXIT;
				
			float r = rand() % (int)round(AppConfig.max);
				
			std::cout << "Random number is [" << r << "]\n";
				
			float da = fdim(r,AppState.a);
			float db = fdim(r,AppState.b);
				
			if(da == db)
				std::cout << "WoW It's a --draw-- \\(" << da << "_" << db << ")/\n";
			else if(da < db)
				std::cout << "Player /*.^/ [" + AppConfig.nickname1 + "] WIN WITH NUMBER (" << AppState.a << ")\n";
			else
				std::cout << "Player \\^.*\\ [" + AppConfig.nickname2 + "] WIN WITH NUMBER (" << AppState.b << ")\n";
					
			AppState.history.push_back(HEntry(AppState.a,AppState.b,r));
		}
	}
	catch(enum AppControlCode &control)
	{
		switch(control)
		{
			case EVT_EXIT:
				std::cout << "Exit called stopping...\n";
			break;
		}
	}

	return 0;
}