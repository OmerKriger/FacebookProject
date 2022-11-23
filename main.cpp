#include <iostream>
using namespace std;
#include "Facebook.h"
#include "supportFunctions.h"
#define TEST 1 // TEST == 0 is no test setup

int main()
{	
	Facebook* facebook = new Facebook;
	if(TEST)
		facebook->__Init__();
	int selection;
	system("cls");
	cout << "Welcome to Facebook !" << endl << endl;
	do
	{
		printMenu();
		cout << "What is you choice ?: " << endl;
		cin >> selection;
		// system("cls"); after test maybe remove note
		actionsForMenu(selection, *facebook);
	
	} while (selection != EXIT);
	
	delete facebook;
}

