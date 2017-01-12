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
	double d = pow(b, 2) - 4 * a * c;

	if (d < 0)
	{
		return 0;
	}
	if (d == 0)
	{
		roots[number] = -b / (2 * a);

		return 1;
	}
	if (d > 0)
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
	double aa, bb;
	if (r <= 0.)
	{
		r = -r;
	}
	aa = -pow(r + sqrt(r2 - q3), 1. / 3.);
	if (aa != 0.)
	{
		bb = q / aa;
	}
	else
	{
		bb = 0.;
	}
	b /= 3.;
	q = aa + bb;
	r = aa - bb;
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
	double q, r, r2, q3;

	q = (pow(b, 2) - 3. * c) / 9.;
	r = (b * (2. * pow(b, 2) - 9. * c) + 27. * d) / 54.;
	r2 = pow(r, 2);
	q3 = pow(q, 3);

	if (r2 < q3)
	{
		return GetRootsNum3(s, r, q3, b, q);
	}
	else
	{
		return GetRootsNum(s, r, q3, b, q, r2);
	}
}

void BringingCoefficients(EquationCoeff &coeff, double a, const double &b, const double &c, const double &d, const double &e)
{
	coeff.b = b / a;
	coeff.c = c / a;
	coeff.d = d / a;
	coeff.e = e / a;
}

void ComputeCanonicCoefficients(EquationCoeff &eqCoeff, CanonicEquationCoeff &canonicCoeff)
{
	canonicCoeff.p = eqCoeff.c - ((3 * pow(eqCoeff.b, 2)) / 8);
	canonicCoeff.q = pow(eqCoeff.b, 3) / 8 - (eqCoeff.b * eqCoeff.c) / 2 + eqCoeff.d;
	canonicCoeff.r = -(3 * pow(eqCoeff.b, 4)) / 256 + (pow(eqCoeff.b, 2) * eqCoeff.c) / 16 - (eqCoeff.d * eqCoeff.b) / 4 + eqCoeff.e;
}

void ComputeSquareCoefficients(SquareCoeff &sqCoeff, CanonicEquationCoeff &canonicCoeff)
{
	sqCoeff.b = sqrt(2 * canonicCoeff.roots[canonicCoeff.numRoots - 1] - canonicCoeff.p);
	sqCoeff.c1 = -(canonicCoeff.q / (2 * sqrt(2 * canonicCoeff.roots[canonicCoeff.numRoots - 1] - canonicCoeff.p)))
		+ canonicCoeff.roots[canonicCoeff.numRoots - 1];
	sqCoeff.c2 = (canonicCoeff.q / (2 * sqrt(2 * canonicCoeff.roots[canonicCoeff.numRoots - 1] - canonicCoeff.p)))
		+ canonicCoeff.roots[canonicCoeff.numRoots - 1];
}

EquationRoots4 Solve4(double a, double b, double c, double d, double e)
{
	if (a == 0)
	{
		throw invalid_argument("Coefficient 'a' must not be equal to zero");
	}

	EquationCoeff eqCoeff;
	CanonicEquationCoeff canCoeff;
	SquareCoeff sqCoeff;

	BringingCoefficients(eqCoeff, a, b, c, d, e);

	ComputeCanonicCoefficients(eqCoeff, canCoeff);

	canCoeff.numRoots = Solve3(canCoeff.roots, -canCoeff.p / 2, -canCoeff.r,
		(canCoeff.r * canCoeff.p - pow(canCoeff.q, 2) / 4) / 2);

	ComputeSquareCoefficients(sqCoeff, canCoeff);

	unsigned numRootsDiOne = Solve2(0, sqCoeff.roots, 1, -sqCoeff.b, sqCoeff.c2);
	unsigned numRootsDiTwo = Solve2(numRootsDiOne, sqCoeff.roots, 1, sqCoeff.b, sqCoeff.c1);

	if (numRootsDiOne == 0 && numRootsDiTwo == 0)
	{
		throw domain_error("No real roots");
	}

	EquationRoots4 equationRoots;

	equationRoots.numRoots = numRootsDiOne + numRootsDiTwo;

	for (unsigned i = 0; i != equationRoots.numRoots; ++i)
	{
		equationRoots.roots[i] = sqCoeff.roots[i] - eqCoeff.b / 4;
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