MainMenuState::MainMenuState()
{
				
}
MainMenuState::~MainMenuState()
{
				
}
//Functions
void MainMenuState::printMenu()
{
				
}
//update
void MainMenuState::update(string &input)
{
				if(input.substr(0,input.find(' ')-1) == "quit")
								this->quit = true;
}