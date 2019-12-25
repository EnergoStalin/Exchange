#include "Map.cpp"
#include "Shell.cpp"

#define PATH "/storage/emulated/0/code/map.txt"

Shell sh;
Map m;

int main(int argc, char **argv) {
				m.Size(15,15);
				m.FromFile(PATH);
				m.FillRect(0,0,15,15,'3');
				m.Save(PATH);
				m.Display();
				
				return 0;
}