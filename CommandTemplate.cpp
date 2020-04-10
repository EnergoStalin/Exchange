#include <iostream>

class GameActor
{

public:
	void jump() {std::cout << "Jump\n";}
	void move();
};
class Command
{
public:
	virtual ~Command();
	virtual void excute(GameActor *);
};

class JumpCommand
{
public:
	void excute(GameActor *actor)
	{
		actor->jump();
	}
};

int main()
{
	JumpCommand jc;
	GameActor ga;
	
	jc.excute(&ga);

	return 0;
}