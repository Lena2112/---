#include "stdafx.h"
#include "../sieve/sieve.h"

BOOST_AUTO_TEST_SUITE(TestGeneratePrimeNumbersSet)

BOOST_AUTO_TEST_CASE(creates_a_set_when_the_upper_limit_numbers_0)
{
	std::set<unsigned int> referenceSet = {};
	BOOST_CHECK(GeneratePrimeNumbersSet(0) == referenceSet);
}

BOOST_AUTO_TEST_CASE(creates_a_set_when_the_upper_limit_numbers_2)
{
	std::set<unsigned int> referenceSet = { 2 };
	BOOST_CHECK(GeneratePrimeNumbersSet(2) == referenceSet);
}

BOOST_AUTO_TEST_CASE(creates_a_set_when_the_upper_limit_numbers_100)
{
	std::set<unsigned int> referenceSet = { 2, 3, 5, 7, 11, 13, 17, 19, 23,
		29, 31, 37, 41, 43, 47, 53, 59,
		61, 67, 71, 73, 79, 83, 89, 97 };
	BOOST_CHECK(GeneratePrimeNumbersSet(100) == referenceSet);
}

#ifdef NDEBUG
BOOST_AUTO_TEST_CASE(when_the_upper_limit_numbers_is_equal_to_the_maximum_value)
{
	BOOST_CHECK(GeneratePrimeNumbersSet(100000000).size() == 5761455);
}
#endif

BOOST_AUTO_TEST_SUITE_END()