#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "state.h"

class MainMenuState : public State
{
				public:
								MainMenuState();
								virtual ~MainMenuState();
								void update(string &input);
								void printMenu();
};

#include "main_menu_state.cpp"

#endif