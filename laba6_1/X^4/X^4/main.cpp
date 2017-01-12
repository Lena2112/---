#include "stdafx.h"
#include "X^4.h"
#include <iterator>
#include <sstream>

using namespace std;

int main()
{
	EquationRoots4 equationRoots;

	cout << "Enter coefficients:\n";

	double numbers[5];
	unsigned number = 0;

	while (cin >> numbers[number] && number < 4)
	{
		++number;
	}

	try
	{
		equationRoots = Solve4(numbers[0], numbers[1], numbers[2], numbers[3], numbers[4]);
	}
	catch (invalid_argument &error)
	{
		cout << "Error: " << error.what() << endl;
		return 1;
	}
	catch (domain_error &error)
	{
		cout << "Error: " << error.what() << endl;
		return 1;
	}

	OutRoots(equationRoots);

	return 0;
}

