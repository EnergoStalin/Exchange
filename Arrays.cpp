#pragma once
#include <iostream>

#include <cstdlib>

using std::cout;
using std::endl;

namespace ArrayTools {
	enum ArrayOutputFormat //For function ShowArray()
	{
		ARRAY_DEFAULT=0,
		ARRAY_LINE,
		ARRAY_TAB_LINE,
		ARRAY_LINE_NO_SPACE
	};

	typedef unsigned short int size_t;

	void fill_int(int arr[], const int size) {
		srand(time(0));
		for(int i = 0; i < size; i++) {
			arr[i] = rand() % 100;
		}
	}

	template<typename T>
	void show(const T arr[], const int size, const int format = ARRAY_DEFAULT) {
		if(format == ARRAY_DEFAULT) {
			for(int i = 0; i < size; i++) {
				cout << "I - " << (i + 1) << "\tValue: " << arr[i] << "\tAt: " << (arr+i) << endl;
			}
		} else if(format == ARRAY_LINE){
			for(int i = 0; i < size; i++) {
				cout << arr[i] << " ";
			} cout << endl;
		} else if(format == ARRAY_TAB_LINE) {
			for(int i = 0; i < size; i++) {
				cout << arr[i] << '\t';
			} cout << endl;
		} else if(format == ARRAY_LINE_NO_SPACE) {
			for(int i = 0; i < size; i++) {
				cout << arr[i];
			} cout << endl;
		}
	}
	
	template<typename T>
	void copy(T *arr, T *to, int size) {
		for(int i = 0; i < size; i++) {
			to[i] = arr[i];
		}
	}
	
	template<typename T>
	bool equals(T *arr,T *to, int size) {
		for(int i = 0; i < size; i++) {
			if(arr[i] != to[i]) { return false; }
		} return true;
	}
	
	template<typename T>
	void assign(T *&arr, T *&to, const int size) {
		for(int i = 0; i < size; i++) {
			arr[i] = to[i];
		}
	}
	
	template<typename T>
	void push_back(T *&arr, int &size, const T value) {
		T *newArr = new T[size + 1];
		for(int i = 0; i < size; i++) {
			newArr[i] = arr[i];
		}
		newArr[size] = value;
		delete[] arr;
		arr = newArr;
		newArr = NULL;
		size++;
	}
	
	template<typename T>
	void pop_back(T *&arr, int &size) {
		T *newArr = new T[--size];
		for(int i = 0; i < size; i++) {
			newArr[i] = arr[i];
		}
		delete[] arr;
		arr = newArr;
		newArr = NULL;
	}

	template<typename T>
	T* link(const T arr1[], const T arr2[], const int size1, const int size2) {
		T *arr3 = new T[size1 + size2];
		for(int i = 0; i < size1; i++) {
			arr3[i] = arr1[i];
		}
		for(int j = 0, k = size1; j < size2; j++, k++) {
			arr3[k] = arr2[j];
		}
		return arr3;
	}

	template<class T>
	void sort(T *&arr,int l)
	{
		for(int j = 0; j < l; j++)
			for(int i = 0; i < l-1; i++)
			{
				T t = arr[i];
				if(arr[i+1] < t) { arr[i] = arr[i+1]; arr[i+1] = t; }
			}
	}

	template<class T>
	void rsort(T *&arr,int l)
	{
		for(int j = 0; j < l; j++)
			for(int i = 0; i < l-1; i++)
			{
				T t = arr[i];
				if(arr[i+1] > t) { arr[i] = arr[i+1]; arr[i+1] = t; }
			}
	}

}
