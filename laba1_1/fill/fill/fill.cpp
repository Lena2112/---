#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

const char beginChar  = 'O';
const char fillChar   = ' ';
const char fillToChar = '.';

using namespace std;
 
bool ValidateInput(int argc)
{
    if (argc != 3)
    {
        cout << "Invalid arguments count." << endl << 
            "Usage: fill.exe <input file> <output file>" << endl;
		return false;
    }
    return true;
}

bool CheckArguments(const ifstream & input, const ofstream & output)
{
    if (!input.is_open() || !output.is_open()) 
    {
        cout << "Failed to open file for reading" << endl;
		return false;
    }
    
    return true;
}

void WriteVector(ifstream & input, vector<string> & lines)
{
	string s;
	while (getline(input, s) && lines.size() < 10)
	{
		lines.push_back(s);
	}
}

void IdentifyStartingPoints(vector< pair<int, int> > & startPoints, vector<string> & lines)
{
	for (size_t i = 0; i < lines.size(); ++i) 
	{
        size_t position = lines[i].find(beginChar);
        if (position != lines[i].npos) 
		{
            startPoints.push_back(pair<int,int>(i, position));
        }
    }
}

void Fill(vector<string> & lines, size_t row, int col) 
{
    if (row > 0 && col > 0 &&  row < lines.size()
        &&  lines[row][col] == fillChar) 
	{
        lines[row][col] = fillToChar;
        Fill(lines, row+1, col);
        Fill(lines, row-1, col);
        Fill(lines, row, col-1);
        Fill(lines, row, col+1);
    }
}

void FindPointFill(vector<string> & lines)
{
	vector< pair<int, int> > startPoints;
    IdentifyStartingPoints(startPoints, lines);

    for (size_t i = 0; i < startPoints.size(); ++i) 
	{
        pair<int, int> & point = startPoints[i];
        lines[point.first][point.second] = fillChar;
        Fill(lines, point.first, point.second);
        lines[point.first][point.second] = beginChar; 
    }
}

void PrintCompletedVector(vector<string> & lines, ofstream & output)
{
	FindPointFill(lines);
 
    for (size_t i = 0; i < lines.size(); ++i)
	{
        output << lines[i] << endl;
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
	ofstream output(argv[2]);

	if (CheckArguments(input, output))
	{
        vector<string> lines;
	    WriteVector(input, lines);
        PrintCompletedVector(lines, output);
	}
    return 0;	
}