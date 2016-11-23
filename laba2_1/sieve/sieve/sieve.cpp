#include "stdafx.h"
#include "sieve.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	unsigned int upperBound;
	if (cin >> upperBound || upperBound > 100000000)
	{
		cout << "sieve.exe [0..100000000]" << endl;
		return 1;
	}

	set<unsigned int> prime = GeneratePrimeNumbersSet(upperBound);
	copy(prime.begin(), prime.end(), ostream_iterator<double>(cout, " "));

	return 0;
}

