#include <fstream>
#include <iostream>

using namespace std;

enum TileType {
	Plaints=0,
	Mountian,
	Lake,
	River
};

class Map {
public:
	Map() : w(0), h(0) {
			this->arr = NULL;
	}
<<<<<<< HEAD
	Map(string version) : Map() {
			this->opt.version = version;
	}
	Map(string version,int w, int h) : Map(version) {
		Size(w,h);
	}
	void FillMap() {
		for(int i = 0; i < opt.height; i++) {
			for(int j = 0; j < opt.width; j++) {
				this->arr[i][j].type = TileType::Plaints;
			}
		}
	}
	void changeVersion(string nver) {
			this->opt.version = nver;
	}
	void MakeMap() {
		if(this->arr != NULL) delete[] this->arr;
		this->arr = new Tile*[opt.height];
		for(int i = 0; i < opt.height; i++) {
			this->arr[i] = new Tile[opt.width];
		}
	}
=======
	Map(string version,int w, int h) : Map() {
		this->opt.version = version;
		Size(w,h);
	}
	void FillMap() {
		for(int i = 0; i < opt.height; i++) {
			for(int j = 0; j < opt.width; j++) {
				this->arr[i][j].type = TileType::Plaints;
			}
		}
	}
	void changeVersion(string nver) {
			this->opt.version = nver;
		}
	void MakeMap() {
		if(this->arr != NULL) delete[] this->arr;
		this->arr = new Tile*[opt.height];
		for(int i = 0; i < opt.height; i++) {
			this->arr[i] = new Tile[opt.width];
		}
		}
>>>>>>> 13e83472ad32b73b6d4f0898880dacf6818ec59a
	void Size(int w, int h) {
			opt.width = w;
			opt.height = h;
			MakeMap();
			FillMap();
<<<<<<< HEAD
	}
	void Display() {
		for(int i = 0; i < opt.height; i++) {
			for(int j = 0; j < opt.width; j++) {
				cout << this->arr[i][j].type << ' ';
			} cout << endl;
		}
	}
	void FromFile(string path) {
		ifstream file(path.c_str(),ios::in | ios::binary);
=======
		}
	void Display() {
		for(int i = 0; i < opt.height; i++) {
			for(int j = 0; j < opt.width; j++) {
				cout << this->arr[i][j].type << ' ';
			} cout << endl;
		}
		}
	void FromFile(string path) {
		ifstream file(path.c_str(),ios::in | ios::binary);
>>>>>>> 13e83472ad32b73b6d4f0898880dacf6818ec59a
		if(file.is_open()) {
				file.read((char*)&opt,sizeof(Option));
				MakeMap();
				for(int i = 0; i < opt.height; i++) {
					for(int j = 0; j < opt.width; j++) {
						file.read((char*)&this->arr[i][j],sizeof(Tile));
					}
				}
				cout << "File readed." << endl;
			  file.close();
		} else cerr << "Fail to open file." << endl;
	}
	void Save(string path) {
		ofstream file (path.c_str(), ios_base::trunc);
		file.close();
		file.open(path.c_str(), ios::out | ios::binary);
		if(file.is_open()) {
			file.write((char*)&opt,sizeof(Option));
			for(int i = 0; i < opt.height; i++) {
					for(int j = 0; j < opt.width; j++) {
						file.write((char*)&this->arr[i][j],sizeof(Tile));
					}
<<<<<<< HEAD
			}
			file.close();
			cout << "Saved." << endl;
		} else cerr << "Cant open file." << endl;
	}
	void FillRect(int x, int y, int w, int h, TileType type) {
		for(int i = 0; i < opt.height; i++) {
			for(int j = 0; j < opt.width; j++) {
				if(((i >= y) && (j >= x)) && ((i <= (y+(h-1))) && (j <= (x+(w-1)))))
					this->arr[i][j].type = type;
		}
	}
=======
			}
			file.close();
			cout << "Saved." << endl;
		} else cerr << "Cant open file." << endl;
	}
	void FillRect(int x, int y, int w, int h, TileType type) {
		for(int i = 0; i < opt.height; i++) {
			for(int j = 0; j < opt.width; j++) {
				if(((i >= y) && (j >= x)) && ((i <= (y+(h-1))) && (j <= (x+(w-1))))) {
					this->arr[i][j].type = type;
				}
			}
		}
>>>>>>> 13e83472ad32b73b6d4f0898880dacf6818ec59a
}
	void GetMapInfo() {
			cout << "Map version: " << opt.version << endl;
				cout << "Rows:" << opt.width << endl;
				cout << "Cols: " << opt.height << endl;
		}
	~Map() {
		for(int i = 0; i < opt.height; i++) {
			delete[] arr[i];
		}
		delete[] arr;

	}
	private:
			class Option {
				public:
					Option() {
						version = "0.1";
						width = 0;
						height = 0;
					}
					Option(string v,int w,int h) {
						version = v;
						width = w;
						height = h;
					}
					string version;
					int width;
					int height;
			};
<<<<<<< HEAD
			class Tile {
				public:
					Tile() : type(TileType::Plaints) {}
					Tile(TileType t) : type(t) {}
					TileType type;
			};
	int w;
=======
			class Tile {
				public:
					Tile() : type(TileType::Plaints) {}
					Tile(TileType t) : type(t) {}

					TileType type; 
			};
	int w;
>>>>>>> 13e83472ad32b73b6d4f0898880dacf6818ec59a
	int h;
	Option opt;
	Tile **arr;

};
