#pragma once

/* string path = "file.tx";

	ifstream fin;
	fin.exceptions(ifstream::badbit | ifstream::failbit);

try {
	cout << "Попытка открыть файл." << endl;
	fin.open(path);
	cout << "Файл успешно открыт." << endl;
	cout << "Чтение файла:" << endl;
	string buff;
	while(!fin.eof()) {
		buff = "";
		getline(fin, buff);
		cout << buff;
	}
	fin.close();
} catch(const exception& ex) {
	cout << ex.what() << endl;
	cout << "Ошибка открытия файла!!!" << endl;
} */