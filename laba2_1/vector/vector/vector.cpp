#include "stdafx.h"
#include "VectorProcessor.h"
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

int _tmain()
{
	vector<double> numbers;
	copy(istream_iterator<double>(cin), istream_iterator<double>(), back_inserter(numbers));

	ProcessVector(numbers);

	copy(numbers.begin(), numbers.end(), ostream_iterator<double>(cout, ", "));

	cout << "\nSize of vector: " << numbers.size() << endl;

	return 0;
}
