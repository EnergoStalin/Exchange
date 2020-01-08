Game::Game()
{
				this->initStates();
}
Game::~Game()
{
				while(!this->states.empty())
				{
								delete this->states.top();
								this->states.pop();
				}
}
//Functions
//initStates
void Game::initStates()
{
				this->states.push(new MainMenuState());
}

//Excute
int Game::Excute()
{
				while(running)
				{
								this->update();
				}
				
				return 0;
}
//UpdateIput
void Game::updateInput()
{
				string input;
				getline(cin,input,'\n');
				
				this->states.top()->update(input);
}

//Update
void Game::update()
{
				this->updateInput();
				if(this->states.top()->isQuit())
				{
								delete this->states.top();
								this->states.pop();
				}
				if(this->states.empty()) running = false;
}