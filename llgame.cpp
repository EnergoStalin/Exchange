#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <random>
#include <ctime>
#include <stdio.h>
#include <cstring>

typedef void (*AppStateCaller)(void);

bool is_digital_string(const char *str)
{
	while(*str != '\0') if(isdigit(*str)) return false; else str++;
	return true;
}

enum AppControlCode
{
	EVT_EXIT = 0x000001,
	EVT_COMMAND_NOT_FOUND
} AppControlCode;

struct AppConfig
{
	AppConfig() {}
	AppConfig(std::string n1, std::string n2, float max = 100, int at = 1) : nickname1(n1), nickname2(n2), count_attempts(at), max(max) {}
	std::string nickname1 = "Player1";
	std::string nickname2 = "Player2";
	std::string exit_token = "e";
	size_t count_attempts = 1;
	float max = 100;
	void load()
	{
		FILE *ptr = fopen("./llgame.cfg","r");

		if(!ptr)
		{
			printf("%s\n", "Dont find config file creating it in same folder.");
			ptr = fopen("./llgame.cfg","w");

			if(!ptr) return;

			fprintf(ptr, "%s\n", "#Follow this config wile syntax and everything will be okay.\n\
				#Supported only listed below options.\
			");
			fprintf(ptr, "%s: %s\n", "nickname1", "Player1");
			fprintf(ptr, "%s: %s\n", "nickname2", "Player2");
			fprintf(ptr, "%s: %c\n", "exit_token", 'e');
			fprintf(ptr, "%s: %d\n", "count_attempts", 1);
			fprintf(ptr, "%s: %d\n", "random_max", 100);

			fclose(ptr);

			return;
		}
		
		char property[60];
		char value[40];

		while(!feof(ptr))
		{
			fscanf(ptr,"%[^:]: %s\n",property,value);
			if(property[0] == '#') continue;
			if(strcmp(property,"nickname1") == 0) this->nickname1 = value;
			else if(strcmp(property,"nickname2") == 0) this->nickname2 = value;
			else if(strcmp(property,"exit_token") == 0) if(is_digital_string(value)) this->exit_token = value; else printf("%s\n", "CONFIG_PARSER::WARNING exit_token must be not numeric value.");
			else if(strcmp(property,"count_attempts") == 0) this->count_attempts = atoi(value);
			else this->max = atoi(value);
		}

		fclose(ptr);
		printf("%s\n", "Loaded config from llgame.cfg");
	}
	
} AppConfig;

struct HEntry
{
	HEntry() {}
	HEntry(float p1,float p2, float r) : p1(p1), p2(p2), r(r) {}
	std::string stat;
	float p1 = 0;
	float p2 = 0;
	float r = 0;
};

std::ostream &operator<<(std::ostream &os, HEntry &h)
{
	os << AppConfig.nickname1 << ": " << h.p1 << "\n" << AppConfig.nickname2 << ": " << h.p2 << "\nRandom: " << h.r << "\nResult: " << h.stat << "\n";

	return os;
}

struct AppState
{
	float a = 0, b = 0;
	void bind(std::string name, AppStateCaller caller)
	{
		binds.emplace(name,caller);
	}
	void ProcessInput(std::string name)
	{
		auto entry = binds.find(name);
		if(entry != binds.end())
		{
			entry->second();
		}
		else
		{
			throw EVT_COMMAND_NOT_FOUND;
		}
	}
	float getInput(std::string &nickname)
	{
		std::string temp;

		while(true)
		{
			try
			{
				std::cout << "[" + nickname + "] Input: ";
				std::cin >> temp;
				std::cin.ignore(37868,'\n');

				try
				{
					return std::stof(temp);
				}
				catch(std::exception &ex)
				{
					ProcessInput(temp);
				}
			}
			catch(enum AppControlCode &e)
			{
				if(e == EVT_COMMAND_NOT_FOUND) std::cout << "Command " << temp << " not found.\n";
				else throw e;
			}
		}
	}
	void unbind(std::string name)
	{
		binds.erase(name);
	}
	std::map<std::string,AppStateCaller> binds;
	std::vector<HEntry> history;
} AppState;

int main(int argc, const char **argv)
{
	AppConfig.load();
	srand((unsigned)time(NULL));

	AppState.bind(AppConfig.exit_token,[]() { throw EVT_EXIT; });
	AppState.bind("h",[]() { for(auto e : AppState.history) { std::cout << e << std::string(20,'*') << '\n'; } });

	try
	{
		while(true)
		{
			AppState.a = AppState.getInput(AppConfig.nickname1);			
			AppState.b = AppState.getInput(AppConfig.nickname2);
				
			float r = rand() % (int)round(AppConfig.max);
				
			std::cout << "Random number is [" << r << "]\n";
				
			float da = abs(r - AppState.a);
			float db = abs(r - AppState.b);
			HEntry ent(AppState.a,AppState.b,r);
				
			if(da == db)
			{
				ent.stat = "--draw--";
				std::cout << "WoW It's a --draw-- \\(" << da << "_" << db << ")/\n";

			}
			else if(da < db)
			{
				ent.stat = "[" + AppConfig.nickname1 + "] WIN";
				std::cout << "/*.^/ [" + AppConfig.nickname1 + "] WIN WITH NUMBER (" << AppState.a << ")\n";
			}
			else
			{
				ent.stat = "[" + AppConfig.nickname2 + "] WIN";
				std::cout << "\\^.*\\ [" + AppConfig.nickname2 + "] WIN WITH NUMBER (" << AppState.b << ")\n";
			}

			AppState.history.push_back(ent);
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