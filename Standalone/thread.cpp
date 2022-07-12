#include <iostream>
#include <thread>
#include <chrono>

#define COUNT 10

void DoWork(int a, int b) {
	int c = a + b;
	for (size_t i = 0; i < c; i++)
	{
		std::cout << "Thread id: " << std::this_thread::get_id() << "\tdoWork()" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds (1000));
	}
}

int main() {
	std::thread thr(DoWork, COUNT, COUNT);
	for (size_t i = 0; i < COUNT; i++)
	{
		std::cout << "Thread id: " << std::this_thread::get_id() << "\tmain()" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds (500));
	}
	thr.join();
				
	return 0;
}