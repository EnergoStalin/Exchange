#include "Arrays.cpp"

int main()
{
	int size = 5;
	int *arr = new int[size];

	ArrayTools::fill_int(arr,size);
	ArrayTools::rsort(arr,size);
	ArrayTools::show(arr,size);

	delete []arr;

	return 0;
}