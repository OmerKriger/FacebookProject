#include <iostream>
using namespace std;
#include "Facebook.h"
#include "supportFunctions.h"
#include "Date.h"

int main()
{	
	Facebook facebook; // create facebook
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
		actionsForMenu(selection, facebook); // make action for the selection from menu
	
	} while (selection != EXIT);

}

