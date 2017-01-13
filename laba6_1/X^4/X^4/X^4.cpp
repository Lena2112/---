#include "stdafx.h"
#include "X^4.h"
#include <math.h>
#include <boost/range/algorithm/transform.hpp>
#include <boost/phoenix.hpp>

using namespace std;

struct EquationCoeff
{
	double b;
	double c;
	double d;
	double e;
};

struct CanonicEquationCoeff
{
	double p;
	double q;
	double r;
	double roots[3];
	unsigned numRoots;
};

struct SquareCoeff
{
	double b;
	double c1;
	double c2;
	double roots[4];
};

unsigned Solve2(const unsigned &number, double* roots, double a, double b, double c)
{
	double const d = pow(b, 2) - 4 * a * c;

	if (d < 0)
	{
		return 0;
	}
	else if (d == 0)
	{
		roots[number] = -b / (2 * a);

		return 1;
	}
	else if (d > 0)
	{
		roots[number] = (-b - sqrt(d)) / 2 * a;
		roots[number + 1] = (-b + sqrt(d)) / 2 * a;

		return 2;
	}
	return 0;
}

unsigned GetRootsNum3(double* s, double r, double q3, double b, double q)
{
	double t = acos(r / sqrt(q3));
	b /= 3.;
	q = -2. * sqrt(q);
	s[0] = q * cos(t / 3.) - 1;
	s[1] = q * cos((t + 2 * M_PI) / 3.) - b;
	s[2] = q * cos((t - 2 * M_PI) / 3.) - b;
	return 3;
}

unsigned GetRootsNum(double* s, double r, double q3, double b, double q, double r2)
{
	double coeffA, coeffB;
	if (r <= 0.)
	{
		r = -r;
	}
	coeffA = -pow(r + sqrt(r2 - q3), 1. / 3.);
	if (coeffA != 0.)
	{
		coeffB = q / coeffA;
	}
	else
	{
		coeffB = 0.;
	}
	b /= 3.;
	q = coeffA + coeffB;
	r = coeffA - coeffB;
	s[0] = q - b;
	s[1] = (-0.5) * q - b;
	s[2] = (sqrt(3.) * 0.5) * fabs(r);
	if (s[2] == 0.)
	{
		return 2;
	}
	else
	{
		return 1;
	}
}


unsigned Solve3(double* s, double b, double c, double d)
{
	double q = (pow(b, 2) - 3. * c) / 9.;
	double r = (b * (2. * pow(b, 2) - 9. * c) + 27. * d) / 54.;
	double r2 = pow(r, 2);
	double q3 = pow(q, 3);

	if (r2 < q3)
	{
		return GetRootsNum3(s, r, q3, b, q);
	}
	return GetRootsNum(s, r, q3, b, q, r2);
}

void BringingCoefficients(EquationCoeff &coeff, double a, const double &b, const double &c, const double &d, const double &e)
{
	coeff.b = b / a;
	coeff.c = c / a;
	coeff.d = d / a;
	coeff.e = e / a;
}

void ComputeCanonicCoefficients(EquationCoeff &equationCoeff, CanonicEquationCoeff &canonicCoeff)
{
	canonicCoeff.p = equationCoeff.c - ((3 * pow(equationCoeff.b, 2)) / 8);
	canonicCoeff.q = pow(equationCoeff.b, 3) / 8 - (equationCoeff.b * equationCoeff.c) / 2 + equationCoeff.d;
	canonicCoeff.r = -(3 * pow(equationCoeff.b, 4)) / 256 + (pow(equationCoeff.b, 2) * equationCoeff.c) / 16 - (equationCoeff.d * equationCoeff.b) / 4 + equationCoeff.e;
}

void ComputeSquareCoefficients(SquareCoeff &squareCoeff, CanonicEquationCoeff &canonicCoeff)
{
	squareCoeff.b = sqrt(2 * canonicCoeff.roots[canonicCoeff.numRoots - 1] - canonicCoeff.p);
	squareCoeff.c1 = -(canonicCoeff.q / (2 * sqrt(2 * canonicCoeff.roots[canonicCoeff.numRoots - 1] - canonicCoeff.p)))
		+ canonicCoeff.roots[canonicCoeff.numRoots - 1];
	squareCoeff.c2 = (canonicCoeff.q / (2 * sqrt(2 * canonicCoeff.roots[canonicCoeff.numRoots - 1] - canonicCoeff.p)))
		+ canonicCoeff.roots[canonicCoeff.numRoots - 1];
}

EquationRoots4 Solve4(double a, double b, double c, double d, double e)
{
	if (a == 0)
	{
		throw invalid_argument("Coefficient 'a' must not be equal to zero");
	}

	EquationCoeff equationCoeff;
	CanonicEquationCoeff canonicCoeff;
	SquareCoeff squareCoeff;

	BringingCoefficients(equationCoeff, a, b, c, d, e);

	ComputeCanonicCoefficients(equationCoeff, canonicCoeff);

	canonicCoeff.numRoots = Solve3(canonicCoeff.roots, -canonicCoeff.p / 2, -canonicCoeff.r,
		(canonicCoeff.r * canonicCoeff.p - pow(canonicCoeff.q, 2) / 4) / 2);

	ComputeSquareCoefficients(squareCoeff, canonicCoeff);

	unsigned const numRootsDiOne = Solve2(0, squareCoeff.roots, 1, -squareCoeff.b, squareCoeff.c2);
	unsigned const numRootsDiTwo = Solve2(numRootsDiOne, squareCoeff.roots, 1, squareCoeff.b, squareCoeff.c1);

	if (numRootsDiOne == 0 && numRootsDiTwo == 0)
	{
		throw domain_error("No real roots");
	}

	EquationRoots4 equationRoots;

	equationRoots.numRoots = numRootsDiOne + numRootsDiTwo;

	for (unsigned i = 0; i != equationRoots.numRoots; ++i)
	{
		equationRoots.roots[i] = squareCoeff.roots[i] - equationCoeff.b / 4;
	}

	return equationRoots;
}

void OutRoots(const EquationRoots4 &roots)
{
	cout << "Roots: ";

	for (unsigned i = 0; i != roots.numRoots; ++i)
	{
		cout << roots.roots[i] << ", ";
	}
	cout << endl;
}