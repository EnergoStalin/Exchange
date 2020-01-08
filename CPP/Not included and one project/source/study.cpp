#include "Map.cpp"
#define PATH "/storage/emulated/0/code/map.bin"
#define VERSION "0.1"

Map m(VERSION);

int main(int argc, char **argv) {
				m.Size(15,15);
				m.GetMapInfo();
				m.Display();
				
				return 0;
}