#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <map>
#include <stack>
#include <cstdlib>
#inclide <fstream>

using namespace std;

#include "../states/MainMenuState.h"

class Game
{
				//Variables
				bool running = true;
				stack<State*> states;
				string clear;
				
				//Functions
				void loadConfig();
				void initStates();
				void update();
				void updateInput();
				void render();
				
				public:
								Game();
								~Game();
								int Excute();
};

#include "../source/game.cpp"
				
#endif