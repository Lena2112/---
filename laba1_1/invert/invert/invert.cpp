﻿#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <iomanip>

#define MATRIX_SIZE 3

typedef double Matrix[MATRIX_SIZE][MATRIX_SIZE];

using namespace std;

bool ValidateInput(int argc)
{
    if (argc != 2)
    {
        cout << "Invalid arguments count." << endl << 
            "Usage: invert.exe <matrix file1>" << endl;
    }
    return (argc == 2);
}

bool CheckingOfArguments(ifstream & input)
{
    if (!input.is_open()) 
    {
        cout << "Failed to open file for reading" << endl;
    }
    
    return (input.is_open());
}

void FillInMatrix(Matrix & matrix, ifstream & input)
{
    for(int i = 0; i < MATRIX_SIZE; i++)
    {
        for(int j = 0; j < MATRIX_SIZE; j++)
        {
            input >> matrix[i][j];
        }
    }
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

double Minor(Matrix const & matrix, int const & i, int const & j)
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

double GetElementNewMatrix(Matrix const & matrix, int const & i, int const & j, double const & determinant)
{
    return pow((double)-1, (i + j)) * Minor(matrix, j, i) / determinant;
}

void PrintNewMatrix(Matrix const & matrix, double const & determinant)
{
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
        {
            cout << setprecision(3) << GetElementNewMatrix(matrix, i, j, determinant) << ' ';
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

    if (CheckingOfArguments(input))
    {
        Matrix matrixInput;
        FillInMatrix(matrixInput, input);
        double determinant = GetDeterminant(matrixInput);
        if (determinant == 0)
        {
            cout << "The determinant of the matrix is zero -> The inverse matrix is not" << endl;
            return 1;
        }
        PrintNewMatrix(matrixInput, determinant);
    }

    return 0;
}