#pragma once
#include <iostream>
#pragma once
#include <cstdlib>

using std::cout;
using std::endl;

namespace ArrayTools {
	enum OutputFormat //For function ShowArray()
	{
		DEFAULT=0,
		LINE,
		TAB_LINE,
		LINE_NO_SPACE
	};

	void FillIntArray(int arr[], const int size) {
		for(int i = 0; i < size; i++) {
			arr[i] = rand() % 10;
		}
	}

	template<typename T>
	void ShowArray(const T arr[], const int size, const int format = DEFAULT) {
		if(format == DEFAULT) {
			for(int i = 0; i < size; i++) {
				cout << "I - " << (i + 1) << "\tValue: " << arr[i] << "\tAt: " << (arr+i) << endl;
			}
		} else if(format == LINE){
			for(int i = 0; i < size; i++) {
				cout << arr[i] << " ";
			} cout << endl;
		} else if(format == TAB_LINE) {
			for(int i = 0; i < size; i++) {
				cout << arr[i] << '\t';
			} cout << endl;
		} else if(format == LINE_NO_SPACE) {
			for(int i = 0; i < size; i++) {
				cout << arr[i];
			} cout << endl;
		}
	}
	
	template<typename T>
	void ArrayCopy(T *arr, T *to, int size) {
		for(int i = 0; i < size; i++) {
			to[i] = arr[i];
		}
	}
	
	template<typename T>
	bool ArrayEquals(T *arr,T *to, int size) {
		for(int i = 0; i < size; i++) {
			if(arr[i] != to[i]) { return false; }
		} return true;
	}
	
	template<typename T>
	void ArrayAssign(T *&arr, T *&to, const int size) {
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
	T* Link_Array(const T arr1[], const T arr2[], const int size1, const int size2) {
		T *arr3 = new T[size1 + size2];
		for(int i = 0; i < size1; i++) {
			arr3[i] = arr1[i];
		}
		for(int j = 0, k = size1; j < size2; j++, k++) {
			arr3[k] = arr2[j];
		}
		return arr3;
	}
	template<typename T>
	T FlipArray(T &arr, int length) {
		T array[length];
		for(int i = length, k = 0; i >= 0, k <= length; i--,k++) {
			array[k] = arr[i];
		}

		return array;
	}
}
