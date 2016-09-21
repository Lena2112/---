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
        cout << "Invalid arguments count." << endl << 
            "Usage: findtext.exe <file name> <text to search>" << endl;
        return false;
    }
    return true;
}

bool CheckingOfArguments(ifstream & input, const string & searchLine)
{
    if (!input.is_open()) 
    {
        cout << "Failed to open file for reading" << endl;
        return false;
    }

    if (searchLine.empty()) 
    {
        cout << "It turned out that it is an empty string" << endl;
        return false;
    }
    
    return true;
}

void SubstringSearch(ifstream & input, const string & searchLine)
{
    int lineNumber = 1;
    bool isStringFound = false;
    string readsLine;

    while (getline(input, readsLine))
    {
        size_t position = readsLine.find(searchLine);
        if (position != -1)
        {
            cout << lineNumber << endl;
            isStringFound = true;
        }
        lineNumber++;
    }

    if (!isStringFound)
    {
        cout << "Not found" << endl;
    }
}

int main(int argc, char * argv[])
{
    setlocale(LC_ALL, "Rus");

    if(!ValidateInput(argc))
    {
        return 1;
    }

    ifstream input(argv[1]);
    string searchLine = argv[2];
    if (CheckingOfArguments(input, searchLine))
    {
        SubstringSearch(input, searchLine);
    }

    return 0;
}