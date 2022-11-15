#include "supportFunctions.h"
#include <iostream>
using namespace std;
bool checkAllocate(void* ptr)
{
	if (ptr == nullptr)
	{
		cout << "Allocation failed\n";
		return false;
	}
	else
		return true;
}