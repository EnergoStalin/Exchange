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
//load config
void Game::loadConfig()
{
				ifstream is("app.txt");
				
				if(is.is_open())
				{
								string buff = "";
								getline(is,buff,'\n');
								this->clear = 
				}
}
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
				system(this->clear);
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