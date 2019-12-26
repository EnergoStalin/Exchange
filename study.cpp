#include "Map.cpp"
#define PATH "/storage/emulated/0/code/map.bin"
#define VERSION "0.1"

int main(int argc, char **argv) {
				Map m(VERSION,15,15);
				m.FromFile(PATH);
				string buff;
				while(true) {
								cout << "$ ";
								cin >> buff;
								cout << buff << endl;
				}
				
				return 0;
}