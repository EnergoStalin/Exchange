#include <thread>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
	int count = 10, duration = 100;
	if(argc >= 2) count = atoi(argv[1]);
	if(argc >= 3) duration = atoi(argv[2]);
	for(int i = 0; i <= count; i++)
	{
		cout << "[";
		for(int i2 = 0; i2 < i; i2++)
		{
			cout << "\e[32m#\e[0m";
		}
		for(int i3 = 0; i3 < count-i; i3++)
		{
			cout << '-';
		}
		cout << "]\t" << i << '/' << count << flush;
		this_thread::sleep_for(chrono::milliseconds(duration));
		cout << "\r\e[K";
	}
				
	return 0;
}