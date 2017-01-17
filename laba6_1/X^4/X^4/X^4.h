#pragma once
#define _USE_MATH_DEFINES 
#include <iostream>
#include <stdio.h>  
#include <conio.h>
#include <locale.h>
#include <math.h>

struct EquationRoots4
{
	unsigned numRoots;
	double roots[4];
};

// ¬ычисл€ем корни кубического уравнени€ ax^4 + bx^3 + cx^2 + dx + e = 0
EquationRoots4 Solve4(double a, double b, double c, double d, double e);
void WriteRoots(const EquationRoots4 &roots);