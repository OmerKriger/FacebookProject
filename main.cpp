#include <iostream>
using namespace std;
#include "Facebook.h"
#include "supportFunctions.h"

//#include "Status.h"
#define TEST 1 // TEST == 0 is no test setup
#define STATUS_TEST 0 


int main()
#include "supportFunctions.h"
{	
	
	Facebook* facebook = new Facebook;
	if(TEST)
		facebook->__Init__();
	int selection;
	system("cls");
	cout << "Welcome to Facebook !" << endl << endl;
	do
	{
		cout << "--------------------------" << endl;
		printMenu();
		cout << "What is your choice ?: " << endl;
		cin >> selection;
		cin.get();
		system("cls");
		actionsForMenu(selection, *facebook);
	
	} while (selection != EXIT);
	
	delete facebook;

	/*if (STATUS_TEST)
	{
		char text[12] = "hello world";
		Status s1(text, sType::tText);
		s1.showStatus();
	}*/

}

