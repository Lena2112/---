#include "stdafx.h"
#include "..\X^4\X^4.h"

using namespace std;

bool RootsAreEqual(const EquationRoots4 &trueRoots, const EquationRoots4 &resultRoots)
{
	for (unsigned i = 0; i != resultRoots.numRoots; ++i)
	{
		if (resultRoots.roots[i] != trueRoots.roots[i])
		{
			return false;
		}
	}
	return true;
}

BOOST_AUTO_TEST_SUITE(slove4_function)

BOOST_AUTO_TEST_CASE(equivalence_test)
{
	EquationRoots4 trueRoots;

	trueRoots.numRoots = 4;
	trueRoots.roots[0] = -2.2360679774997898;
	trueRoots.roots[1] = 2.2360679774997898;
	trueRoots.roots[2] = -3.7320508075688772;
	trueRoots.roots[3] = -0.26794919243112236;

	EquationRoots4 resultRoots = Solve4(1, 4, -4, -20, -5);

	BOOST_CHECK(RootsAreEqual(trueRoots, resultRoots));
}

BOOST_AUTO_TEST_CASE(when_for_a_large_1)
{
	EquationRoots4 trueRoots;

	trueRoots.numRoots = 2;
	trueRoots.roots[0] = -3.1611377728318026;
	trueRoots.roots[1] = 2.5086228038591316;

	EquationRoots4 resultRoots = Solve4(3, 6, -18, -30, -25);
	BOOST_CHECK(RootsAreEqual(trueRoots, resultRoots));
}

BOOST_AUTO_TEST_CASE(when_for_a_less_1)
{
	EquationRoots4 trueRoots;

	trueRoots.numRoots = 2;
	trueRoots.roots[0] = -3.8661138415830827;
	trueRoots.roots[1] = 2.1405655169601401;

	EquationRoots4 resultRoots = Solve4(-4, -8, 30, 7, 10);
	BOOST_CHECK(RootsAreEqual(trueRoots, resultRoots));
}

BOOST_AUTO_TEST_CASE(when_a_is_equal_to_zero)
{
	BOOST_CHECK_THROW(Solve4(0, 4, -4, -20, -5), invalid_argument);
}

BOOST_AUTO_TEST_CASE(when_there_is_no_real_roots)
{
	BOOST_CHECK_THROW(Solve4(1, 2, 3, 4, 5), domain_error);
}

BOOST_AUTO_TEST_SUITE_END()