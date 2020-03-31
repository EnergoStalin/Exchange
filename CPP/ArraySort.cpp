#include <iostream>

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

template<class T>
void printarr(T arr, int size)
{
	for(int i = 0; i < size; i++)
	{
		std::cout << arr[i] << '\n';
	}
}

int main(int argc, char **argv)
{
	int *arr = new int[10]{1000,1,740,1,4,89,12,44,112,78};

	sort(arr,10);
	printarr(arr,10);

	rsort(arr,10);
	printarr(arr,10);

	delete []arr;


	return 0;
}