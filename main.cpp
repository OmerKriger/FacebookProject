#include <iostream>
using namespace std;
#include "Facebook.h"
#define TEST 1

void main()
{	
	Facebook* facebook = new Facebook;
	if(TEST)
		facebook->__Init__();
	int action;
	do
	{
		
		facebook->printMenu();
		cin >> action;
	} while (action == 12);
	
}

