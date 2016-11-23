#include "stdafx.h"
#include "sieve.h"
using namespace std;

vector<bool> InitVector(unsigned int upperBound)
{
	vector<bool> primeSet(upperBound + 1, true);
	if (upperBound >= 2)
	{
		primeSet[0] = primeSet[1] = false;
		for (unsigned int i = 2; i*i <= upperBound; ++i)
		{
			if (primeSet[i])
			{
				for (unsigned int j = i * i; j <= upperBound; j += i)
				{
					if (primeSet[j])
					{
						primeSet[j] = false;
					}
				}
			}
		}
	}
	else
	{
		primeSet = {};
	}
	return primeSet;
}

set<unsigned int> GeneratePrimeNumbersSet(unsigned int upperBound)
{
	vector<bool> tmpSet = InitVector(upperBound);

	set<unsigned int> result;
	if (!tmpSet.empty())
	{
		result.insert(2);
	}
	for (unsigned int i = 3; i < upperBound; i += 2)
	{
		if (tmpSet[i])
		{
			result.insert(i);
		}
	}

	return result;
}