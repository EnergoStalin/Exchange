#include "stdafx.h"

void Foo(int v) {
	if(v < 0) {
		throw exception();
	}

	cout << v << endl;
}

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "ru");
	
	try {
		Foo(-55);
	} catch(const exception &ex) {
		cout << "Мы поймали " << ex.what() << endl;
	}

	cin.get();
	return 0;
}