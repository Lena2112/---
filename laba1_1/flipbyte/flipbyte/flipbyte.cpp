#include "stdafx.h"
#include <iostream>

using namespace std;

bool ValidateInput(int argc)
{
	if (argc != 2)
    {
        cout << "Invalid arguments count.\n"<< 
			"Usage: flipbyte.exe <входной байт>\n";
        return 0;
    }
	return 1;
}

bool ValidateTheVariables(int inputByte)
{
	if (inputByte < 0 || inputByte > 255) 
    {
        cout << "Number entered should be from 0 to 255\n";
        return 0;
    }
	
	return 1;
}

int main(int argc, char * argv[])
{
    setlocale (LC_ALL, "Rus");

    if(!ValidateInput(argc))
		return 1;

    int inputByte = atoi(argv[1]);
	if (ValidateTheVariables(inputByte))	   
	{
		int i;
	    int mod;
	    long double_ = 0;
		for (int i = 0; inputByte>0; i++) 
	{
	
		mod =  inputByte % 2;
		inputByte = (inputByte - mod) / 2;
		double_ += mod * pow((double)10,i);
	}
	cout << double_;
	}

    return 0;
}
