#include <iostream>
using namespace std;
#include "Facebook.h"
#include "supportFunctions.h"
#include "Date.h"
#define TEST 1 // TEST == 0 is no test setup

int main()
{	

	Facebook* facebook = new Facebook; // create facebook
	if(TEST) // Installiztion for defualt users, pages, connections, statuses and ect. (Only when TEST define isnt 0)
		facebook->__Init__();
	int selection;
	system("cls"); // clear chat
	cout << "----------------- Welcome to Facebook ! -----------------" << endl << endl; 
	cout << "System notice: Please be aware the typing is case sensitive in names" << endl;
	do
	{
		cout << "--------------------------" << endl;
		printMenu();
		cout << "--------------------------" << endl << endl;
		cout << "What is your choice ?: " << endl;
		cin >> selection;
		cin.get(); // clear the buffer
		system("cls"); // clear chat after selection
		actionsForMenu(selection, *facebook); // make action for the selection from menu
	
	} while (selection != EXIT);

	delete facebook;

}

