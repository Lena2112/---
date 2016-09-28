#include "stdafx.h"
#include <iostream>

using namespace std;

bool ValidateInput(int argc)
{
    if (argc != 2)
    {
        cout << "Invalid arguments count." << endl <<
            "Usage: flipbyte.exe <входной байт>" << endl;
		return false;
    }
    return true;
}

bool CheckingArguments(int inputByte)
{
    if (inputByte < 0 || inputByte > 255) 
    {
        cout << "Number entered should be from 0 to 255" << endl;
		return false;
    }
    
    return true;
}

void NumberReverseOrderBits(int inputByte)
{
    int bitNumber = 0;
    int outputByte = 0;
    int twoInDegree = 128;
    while (bitNumber != 8)
    {
        if ((inputByte != 0) && (inputByte & 1))
        {
            outputByte += twoInDegree;
        }
        inputByte >>= 1;
        ++bitNumber;
        twoInDegree /= 2;
    } 
    cout << outputByte << endl;
}

int main(int argc, char * argv[])
{
    setlocale(LC_ALL, "Rus");

    if(!ValidateInput(argc))
    {
        return 1;
    }

    int inputByte = atoi(argv[1]);

    if (CheckingArguments(inputByte))       
    {
        NumberReverseOrderBits(inputByte);
    }
    return 0;
}