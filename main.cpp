#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void doWork(int a, int b) {
				while(true) {
								cout<< "Thread id: " << this_thread::get_id() << "\tdoWork" << endl;
								this_thread::sleep_for(chrono:: milliseconds (1000));
				}
}

int main() {
				thread th(doWork,3,4);
				while(true) {
								cout<< "Thread id: " << this_thread::get_id() << "\tmain" << endl;
								this_thread::sleep_for(chrono:: milliseconds (500));
				}
				th.join();
				
				return 0;
}