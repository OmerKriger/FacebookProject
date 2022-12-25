#include <iostream>
#include "Utilities.h"
using namespace std;

int main()
{	
	Utilities UT; // create Utilities and facebook
	int selection;
	system("cls"); // clear chat
	cout << "----------------- Welcome to Facebook ! -----------------" << endl << endl; 
	cout << "System notice: Please be aware the typing is case sensitive in names" << endl << endl;
	do
	{
		cout << "--------------------------" << endl;
		UT.printMenu();
		cout << "--------------------------" << endl << endl;
		cout << "What is your choice ?: " << endl;
		cin >> selection;
		cin.get(); // clear the buffer
		system("cls"); // clear chat after selection
		UT.actionsForMenu(selection); // make action for the selection from menu
	
	} while (selection != EXIT);

}

