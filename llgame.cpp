#include <iostream>
#include <list>
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
	EVT_COMMAND_NOT_FOUND,
	SAVE_FAILED
} AppControlCode;

struct AppConfig
{
	AppConfig() {}
	AppConfig(std::string n1, std::string n2, float max = 100, int at = 1) : nickname1(n1), nickname2(n2), count_attempts(at), max(max) {}
	std::string nickname1 = "Player1";
	std::string nickname2 = "Player2";
	std::string exit_token = "e";
	size_t count_attempts = 1;
	size_t h_cap = 5;
	float max = 100;
	void save()
	{
		printf("%s\n","Will be added soon.");
	}
	void load()
	{
		FILE *ptr = fopen("./llgame.cfg","r");

		if(!ptr)
		{
			printf("%s\n", "Dont find config file creating it in same folder.");
			ptr = fopen("./llgame.cfg","w");

			if(!ptr) return;

			fprintf(ptr, "%s\n", "#Follow this config file syntax and everything will be okay.\n#Supported only listed below options.");
			fprintf(ptr, "%s\n", "#Max max properties length is 20 if it be larger programm will terminated with segmentation fault.");
			fprintf(ptr, "%s: %s\n", "nickname1", "Player1");
			fprintf(ptr, "%s: %s\n", "nickname2", "Player2");
			fprintf(ptr, "%s: %c\n", "exit_token", 'e');
			fprintf(ptr, "%s: %d\n", "store_history", 5);
			fprintf(ptr, "%s: %d\n", "count_attempts", 1);
			fprintf(ptr, "%s: %d\n", "random_max", 100);

			fclose(ptr);

			return;
		}
		
		char string[256];
		char property[60];
		char value[20];

		while(fgets(string,256,ptr) != NULL)
		{
			if(strlen(string) == 0) continue; else if(string[0] == '#') continue;
			sscanf(string,"%[^:]: %s",property,value);
			if(strcmp(property,"nickname1") == 0) this->nickname1 = value;
			else if(strcmp(property,"nickname2") == 0) this->nickname2 = value;
			else if(strcmp(property,"store_history") == 0) {
				this->h_cap = atoi(value);
				if(this->h_cap > 100 || this->h_cap <= 0)
				{
					printf("%s\n", "CONFIG_PARSER::WARNING History cap must be in interval 1-100. Option ignored.");
					this->h_cap = 5;
				}
			}
			else if(strcmp(property,"exit_token") == 0)
				if(is_digital_string(value))
					this->exit_token = value;
				else
					printf("%s\n", "CONFIG_PARSER::WARNING exit_token must be not numeric value.");
			else if(strcmp(property,"count_attempts") == 0)
			{
				this->count_attempts = atoi(value);
				if(this->count_attempts <= 0 || this->count_attempts > 10000)
				{
					printf("%s\n", "CONFIG_PARSER::WARNING Attempts count must be in interval 1-10000. Option ignored.");
					this->count_attempts = 1;
				}
			}
			else if(strcmp(property,"random_max") == 0) this->max = atoi(value);
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
	os <<
		AppConfig.nickname1 <<
		": " <<
		h.p1 <<
		"\n" <<
		AppConfig.nickname2 <<
		": " <<
		h.p2 <<
		"\nRandom: " <<
		h.r <<
		"\nResult: " <<
		h.stat <<
		"\n";

	return os;
}

struct AppState
{
	std::vector<float> a, b;
	void bind(std::string name, AppStateCaller caller)
	{
		binds.emplace(name,caller);
	}
	void h_add_note(HEntry ent)
	{
		if(history.size() >= AppConfig.h_cap) history.pop_back();
		history.push_front(ent);
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
	std::list<HEntry> history;
} AppState;

int main(int argc, const char **argv)
{
	AppConfig.load();
	srand((unsigned)time(NULL));

	AppState.bind(AppConfig.exit_token,[]() { throw EVT_EXIT; });
	AppState.bind("h",[]() {
		for(auto e : AppState.history)
			std::cout << e << std::string(20,'*') << '\n';
	});
	AppState.bind("at",[]() {
		std::cin >> AppConfig.count_attempts;
		if(AppConfig.count_attempts <= 0 || AppConfig.count_attempts > 10000)
		{
			std::cout << "Attempts count must be in interval 1-10000. Set as default 1." << '\n';
			AppConfig.count_attempts = 1;
		}
		else
			std::cout << 
				"Attemts count changed for this session to " <<
				AppConfig.count_attempts <<
				" to store current session setting permamently value run 's' command" << 
				'\n';
	});
	AppState.bind("max",[]() {
		std::cin >> AppConfig.max;
		std::cout <<
			"Max random number changed for this session to " <<
			AppConfig.max <<
			" to store current session setting permamently value run 's' command" <<
			'\n';
	});
	AppState.bind("h_cap",[]() {
		std::cin >> AppConfig.h_cap;
		if(AppConfig.h_cap > 100 || AppConfig.h_cap <= 0)
		{
			std::cout << 
				"History size must be in interval 1-10000. Option ignored.\n";
		}
		else
			std::cout <<
			"History stored size changed for this session to " <<
			AppConfig.h_cap <<
			" to store current session setting permamently value run 's' command" <<
			'\n';
	});
	AppState.bind("s",[]() {
		AppConfig.save();
		std::cout <<
		"Current settings saved to config file." <<
		'\n';
	});

	try
	{
		while(true)
		{
			AppState.a.clear();
			AppState.b.clear();
			for(size_t i = 0; i < AppConfig.count_attempts; i++)
				AppState.a.push_back(AppState.getInput(AppConfig.nickname1));
			for(size_t i = 0; i < AppConfig.count_attempts; i++)
				AppState.b.push_back(AppState.getInput(AppConfig.nickname2));
				
			float r = rand() % (int)round(AppConfig.max);
				
			std::cout << "Random number is [" << r << "]\n";
			
			float da,db;

			if(AppConfig.count_attempts == 1)
			{
				da = abs(r - AppState.a.back());
				db = abs(r - AppState.b.back());
			}
			else
			{
				da = abs(r - AppState.a.back());
				db = abs(r - AppState.b.back());
				float dat, dbt;
				for(size_t i = 0; i <= AppConfig.count_attempts; i++) //TODO: Fix bug more than 2 attempts
				{
					dat = abs(r - AppState.a[i]);
					dbt = abs(r - AppState.b[i]);
					if(da > dat) da = dat;
					if(db > dbt) db = dbt;
				}
			}
			HEntry ent(AppState.a.back(),AppState.b.back(),r);
				
			if(da == db)
			{
				ent.stat = "--draw--";
				std::cout << "WoW It's a --draw-- \\(" << da << "_" << db << ")/\n";

			}
			else if(da < db)
			{
				ent.stat = "[" + AppConfig.nickname1 + "] WIN";
				std::cout << "/*.^/ [" + AppConfig.nickname1 + "] WIN WITH NUMBER (" << AppState.a.back() << ")\n";
			}
			else
			{
				ent.stat = "[" + AppConfig.nickname2 + "] WIN";
				std::cout << "\\^.*\\ [" + AppConfig.nickname2 + "] WIN WITH NUMBER (" << AppState.b.back() << ")\n";
			}

			AppState.h_add_note(ent);
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