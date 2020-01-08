#ifndef STATE_H
#define STATE_H

class State
{
				protected:
								bool quit = false;
								
				public:
								State();
								virtual ~State();
								
								bool isQuit();
								virtual void update(string &input);
};
								
#include "state.cpp"
								
#endif