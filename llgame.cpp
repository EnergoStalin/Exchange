#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <map>
#include <cmath>
#include <random>
#include <ctime>
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
		std::fstream fs("./llgame.cfg",std::ios::in);

		if(!fs.is_open()) { std::cout << "Save failed.\n"; return; }

		std::string filebuff,linebuff;
		size_t pos;
		while(getline(fs,linebuff,'\n'))
		{
			if(linebuff.length() == 0) continue; else if(linebuff.at(0) == '#') { filebuff += linebuff; continue; }
		}


		filebuff += "\n";
		filebuff += "nickname1: " + this->nickname1 + "\n";
		filebuff += "nickname2: " + this->nickname2 + "\n";
		filebuff += "exit_token: " + this->exit_token + "\n";
		filebuff += "h_cap: " + std::to_string(this->h_cap) + "\n";
		filebuff += "random_max: " + std::to_string(this->max) + "\n";
		filebuff += "count_attempts: " + std::to_string(this->count_attempts) + "\n";
		
		fs.close();
		fs.open("./llgame.cfg",std::ios::trunc | std::ios::out);

		fs << filebuff;
		fs.close();


		std::cout << "Saved successfuly.\n";
	}
	void load()
	{
		std::fstream of("./llgame.cfg",std::ios::in);

		if(!of.is_open())
		{
			std::cout << "Dont find config file creating it in same folder.\n";
			of.open("./llgame.cfg",std::ios::out);

			if(of.is_open()) return;

			of << "#Follow this config file syntax and everything will be okay.\n#Supported only listed below options.\n";
			of << "#Max max properties length is 20 if it be larger programm will terminated with segmentation fault.\n";
			of << "nickname1: Player1";
			of << "nickname2: Player2";
			of << "exit_token: e";
			of << "store_history: 5";
			of << "count_attempts: 1";
			of << "random_max: 100";

			of.close();

			return;
		}
		
		std::string buff, key, value;

		while(getline(of,buff,'\n'))
		{
			if(buff.length() == 0 || buff.at(0) == '#') continue;
			size_t pos = buff.find(':');
			key = buff.substr(0,pos);
			value = buff.substr(pos+2);
			if(key == "nickname1") this->nickname1 = value;
			else if(key == "nickname2") this->nickname2 = value;
			else if(key == "store_history") {
				this->h_cap = std::stoi(value);
				if(this->h_cap > 100 || this->h_cap <= 0)
				{
					std::cout << "CONFIG_PARSER::WARNING History cap must be in interval 1-100. Option ignored.\n";
					this->h_cap = 5;
				}
			}
			else if(key == "exit_token")
				if(is_digital_string(value.c_str()))
					this->exit_token = value;
				else
					std::cout << "CONFIG_PARSER::WARNING exit_token must be not numeric value.\n";
			else if(key == "count_attempts")
			{
				this->count_attempts = std::stoi(value);
				if(this->count_attempts <= 0 || this->count_attempts > 10000)
				{
					std::cout << "CONFIG_PARSER::WARNING Attempts count must be in interval 1-10000. Option ignored.\n";
					this->count_attempts = 1;
				}
			}
			else if(key == "random_max") this->max = std::stoi(value);
		}

		of.close();
		std::cout << "Loaded config from llgame.cfg\n";
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
		std::cout << "[at] Prompt: ";
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
				" to save current session setting run 's' command" << 
				'\n';
	});
	AppState.bind("max",[]() {
		std::cout << "[max] Prompt: ";
		std::cin >> AppConfig.max;
		std::cout <<
			"Max random number changed for this session to " <<
			AppConfig.max <<
			" to save current session setting run 's' command" <<
			'\n';
	});
	AppState.bind("h_cap",[]() {
		std::cout << "[h_cap] Prompt: ";
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
			" to save current session setting run 's' command" <<
			'\n';
	});
	AppState.bind("s",[]() {
		AppConfig.save();
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
				for(size_t i = 0; i < AppConfig.count_attempts; i++) //TODO: Fix bug more than 2 attempts
				{
					dat = abs(r - AppState.a[i]);
					dbt = abs(r - AppState.b[i]);
					if(da > dat) { /*std::cout << "da > dat\t" << da << '>' << dat << '\n';*/ da = dat; }
					if(db > dbt) { /*std::cout << "db > dbt\t" << db << '>' << dbt << '\n';*/ db = dbt; }
				}
			}
			HEntry ent((r - da),(r - db),r);
				
			if(da == db)
			{
				ent.stat = "--draw--";
				std::cout << "WoW It's a --draw-- \\(" << (r - da) << "_" << (r - db) << ")/\n";

			}
			else if(da < db)
			{
				ent.stat = "[" + AppConfig.nickname1 + "] WIN";
				std::cout << "/*.^/ [" + AppConfig.nickname1 + "] WIN WITH NUMBER (" << (r - da) << ")\n";
			}
			else
			{
				ent.stat = "[" + AppConfig.nickname2 + "] WIN";
				std::cout << "\\^.*\\ [" + AppConfig.nickname2 + "] WIN WITH NUMBER (" << (r - db) << ")\n";
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