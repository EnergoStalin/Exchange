State::State()
{
				
}
State::~State()
{
				
}
//Functions
void State::update(string &input)
{
				if(input == "quit") this->quit = true;
}
bool State::isQuit()
{
				return this->quit;
}