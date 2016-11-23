#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <iomanip>

const int MATRIX_SIZE = 3;

typedef double Matrix[MATRIX_SIZE][MATRIX_SIZE];

using namespace std;

bool ValidateInput(int argc)
{
    if (argc != 2)
    {
        cout << "Invalid arguments count." << endl << 
            "Usage: invert.exe <matrix file1>" << endl;
		return false;
    }
    return true;
}

bool CheckArguments(const ifstream & input)
{
    if (!input.is_open()) 
    {
        cout << "Failed to open file for reading" << endl;
		return false;
    }
    
    return true;
}


//refactore me
bool FillMatrix(Matrix & matrix, ifstream & input)
{
    for(int i = 0; i < MATRIX_SIZE; ++i)
    {
        for(int j = 0; j < MATRIX_SIZE; ++j)
        {
			if(!input)
			{
				return false;
			}
            input >> matrix[i][j];
        }
    }
	return true;
}

double GetDeterminant(Matrix const & matrix)
{
    return matrix[0][0] * matrix[1][1] * matrix[2][2] 
           + matrix[0][1] * matrix[1][2] * matrix[2][0] 
           + matrix[0][2] * matrix[1][0] * matrix[2][1]
           - matrix[0][2] * matrix[1][1] * matrix[2][0] 
           - matrix[0][0] * matrix[1][2] * matrix[2][1] 
           - matrix[0][1] * matrix[1][0] * matrix[2][2];
}

double GetMinorMiniMatrix(Matrix const & matrix, int i, int j)
{
    double value[4];
    int index = 0;
    for (int k = 0; k < MATRIX_SIZE; ++k)
    {
        if (k != i)
        {
            for (int h = 0; h < MATRIX_SIZE; ++h)
            {
                if (h != j)
                {
                    value[index] = matrix[k][h];
                    index++;
                }
            }
        }
    }
    return value[0] * value[3] - value[1] * value[2];
}

double GetInvertedMatrixElement(Matrix const & matrix, int i, int j, double determinant)
{
    return pow((double)-1, (i + j)) * GetMinorMiniMatrix(matrix, j, i) / determinant;
}

//rename
void PrintInvertMatrix(Matrix const & matrix, double determinant)
{
    for (int i = 0; i < MATRIX_SIZE; ++i)
    {
        for (int j = 0; j < MATRIX_SIZE; ++j)
        {
            cout << fixed << setprecision(3) << GetInvertedMatrixElement(matrix, i, j, determinant) << ' ';
        }
        cout << endl;
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

    if (CheckArguments(input))
    {
        Matrix matrixInput;
		if (!FillMatrix(matrixInput, input))
		{
			cout << "Few data" << endl;
			return 1;
		}
        double determinant = GetDeterminant(matrixInput);
        if (determinant == 0)
        {
            cout << "The determinant of the matrix is zero -> The inverse matrix is not" << endl;
            return 1;
        }
        PrintInvertMatrix(matrixInput, determinant);
    }

    return 0;
}
