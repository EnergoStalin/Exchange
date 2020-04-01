#include <iostream>

#include "obj.h"

#define TEST_PATH "/storage/emulated/0/code/Exchange/CPP/objloader/obj/Handgun_obj.obj"

int main(int argc, char **argv)
{
	ObjLoader ol(TEST_PATH);

	std::cout << '[' << ol.getGroup(0)->getName() << "] object count " << ol.getGroup(0)->objCount() << '\n';


	return 0;
}