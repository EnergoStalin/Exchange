#include <iostream>
#include "Arrays.cpp"
#include "arg.cpp"

using namespace ArrayTools;

int main(int argc, char **argv) {
	Arg arg(argc,argv);
	if(arg.has("-quit"))
	{
		cout << "Has Quit.\n";

		return 0;
	}

	int size = 10;
	int *arr = new int[size];
	int *arr2 = new int[size];
	
	fill_int_array(arr2,size);
	fill_int_array(arr,size);
	int *arr3 = link_array(arr,arr2,size,size);
	show_array(arr,size,ARRAY_LINE);
	show_array(arr2,size,ARRAY_LINE);
	int size2 = size*2;
	push_back_array(arr3,size2,999);
	show_array(arr3,size2,ARRAY_LINE);
				
	delete []arr;
	delete []arr2;
	delete []arr3;
				
	return 0;
}