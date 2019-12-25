#include <fstream>
#include <iostream>

using namespace std;

class Map {
public:
	Map() : w(0), h(0) {
			this->arr = NULL;
	}
	Map(int w, int h) : Map() {
		this->w = w;
		this->h = h;
		MakeMap();
		FillMap();
	}
	void FillMap() {
		for(int i = 0; i < this->h; i++) {
			for(int j = 0; j < this->w; j++) {
				this->arr[i][j].type = '0';
			}
		}
	}
	void MakeMap() {
		if(this->arr != NULL) delete[] this->arr;
		this->arr = new Tile*[this->h];
		for(int i = 0; i < this->h; i++) {
			this->arr[i] = new Tile[this->w];
		}
	}
	void Size(int w, int h) {
			this->w = w;
			this->h = h;
			MakeMap();
			FillMap();
		}
	void Display() {
		for(int i = 0; i < this->h; i++) {
			for(int j = 0; j < this->w; j++) {
				cout << this->arr[i][j].type << ' ';
			} cout << endl;
		}
	}
	void FromFile(string path) {
		ifstream file(path.c_str());
		if(file.is_open()) {
			string line;
			int X = 0, Y = 0;
			while(getline(file,line)) {
				if(line.length() == this->w) {
					for(;X < line.length(); X++) {
						this->arr[Y][X].type = line[X];
					}
					Y++;
					X = 0;
				} else  {
					cerr << "Dont map." << endl;
					break;	
				}
			} file.close();
		} else cerr << "Fail to open file." << endl;
	}
	void Save(string path) {
		ofstream file (path.c_str(), ios_base::trunc);
		file.close();
		file.open(path.c_str(), ios_base::out);
		if(file.is_open()) {
			for(int i = 0; i < this->h; i++) {
				for(int j = 0; j < this->w; j++) {
					file << this->arr[i][j].type;
				} file << endl;
			}
			file.close();
			cout << "Saved." << endl;
		} else cerr << "Save error." << endl;
	}
	void FillRect(int x, int y, int w, int h, char type) {
		for(int i = 0; i < this->h; i++) {
			for(int j = 0; j < this->w; j++) {
				if(((i >= y) && (j >= x)) && ((i <= (y+(h-1))) && (j <= (x+(w-1))))) {
					this->arr[i][j].type = type;
				}
			}
		}
	}
	~Map() {
		for(int i = 0; i < this->h; i++) {
			delete[] arr[i];
		}
		delete[] arr;
		cout << "Memory free." << endl;
	}
	private:
			class Tile {
				public:
					Tile() : type('0') {}
					Tile(char t) : type(t) {}
					char type; 
			};
	int w;
	int h;
	Tile **arr;
};
