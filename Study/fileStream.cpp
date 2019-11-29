#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

/*
* File Streams
* fstream (File stream) Reading && Writing
* ifstream (Input file stream) Reading
* ofstream (Output file stream) Writing
* ofstream fout;
*	fout.open(path, ofstream::trunc(app));
*	if(fout.is_open()) {
*		fout << var;
*   } else cout << "Fail" << endl;
*/

class Setting {
public:
	Setting() {
		this->setting = "";
		this->value = "";
	}
	string getId() {
		return this->setting;
	}
	string getValue() {
		return this->value;
	}
	void setId(string id) {
		this->setting = id;
	}
	void setVal(string val) {
		this->value = val;
	}
private:
	string setting;
	string value;
};

bool Has(const string at, char c) {
	bool has = false;
	for(int i = 0; i < at.length(); i++) {
		if(at.at(i) == '.')  return true;
	} return false;
}

string getPath() {
	string path = "";
	do {
		cout << "Введите путь файла: ";
		cin >> path;
	} while(!Has(path,'.'));

	return path;
}
/*
if(argc == 2) {
	if(Has((string)argv[1], '.')) {
		path = (string)argv[1];
	} else {
    	path = getPath();
	}
} else {
	path = getPath();
}

/////////////////////////
* Fstream using
////////////////////////

fstream fs;
fs.open(path, fstream::in | fstream::out | fstream::app);
if(fs.is_open()) {
	int choice = 0;
	string str;
	cout << "1. Записать в файл." << endl;
	cout << "2. Считать файл." << endl;
	cout << ":";
	do {
		cin >> choice;
	} while (cin.fail());
	switch (choice)
	{
	case 1:
		SetConsoleCP(866);
		cout << "Введите строку без пробелов: " << endl;
		cin >> str;
		fs << str << '\n';
		SetConsoleCP(1251);
		break;
	case 2:
		while(getline(fs,str)) {
			cout << str << endl;
		}
		break;
	
	default: cout << "Ошибка." << endl;
		break;
	}
} else {
	cout << "Ошибка." << endl;
	return 1;
}
fs.close();

/////////////////////////
* Object writing
////////////////////////

ofstream fout;
fout.open(path, ofstream::app);
if(fout.is_open()) {
	Pixel px;
	px.FillFromConsole();
	fout.write((char*)&px, sizeof(Pixel));
} else {
	cout << "Ошибка записи." << endl;
	return 1;
}
fout.close();	

ifstream fin;
fin.open(path);
if(fin.is_open()) {
	Pixel px2;
	while(fin.read((char*)&px2, sizeof(Pixel))) {
		px2.Print();
	}
} else {
	cout << "Ошибка чтения." << endl;
	return 1;
}
fin.close();
*/