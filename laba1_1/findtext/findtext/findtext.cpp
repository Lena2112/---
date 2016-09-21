#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

bool ValidateInput(int argc)
{
	if (argc != 3)
    {
        cout << "Invalid arguments count.\n"<< 
			"Usage: findtext.exe <file name> <text to search>\n";
        return 0;
    }
	return 1;
}

bool ValidateTheVariables(ifstream &input, const string stringToFind)
{
	if (!input.is_open()) 
    {
        cout << "Failed to open file for reading\n";
        return 0;
    }

	if (stringToFind == "") 
    {
        cout << "It turned out that it is an empty string\n";
        return 0;
    }
	
	return 1;
}

void SubstringSearch(ifstream &input, const string stringToFind)
{
	int lineNumber = 1;
    bool stringIsFound = false;
    string readsAString;

	while (getline(input, readsAString))
    {
        size_t position = readsAString.find(stringToFind);
        if (position != -1)
        {
            printf ("%d\n",lineNumber);
            stringIsFound = true;
        }
        lineNumber++;
    }

	if (!stringIsFound)
        cout << "Not found";
}

int main(int argc, char * argv[])
{
    setlocale (LC_ALL, "Rus");

    if(!ValidateInput(argc))
		return 1;

    ifstream input(argv[1]);
    string stringToFind = argv[2];
	if (ValidateTheVariables(input, stringToFind))	   
        SubstringSearch(input, stringToFind);

    return 0;
}