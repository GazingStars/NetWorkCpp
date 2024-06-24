#pragma once
#include "ActivationFunction.h"
#include <cmath>
#include <math.h>


class Tangent : public ActivationFunctions
{
	double activate(double x)const override
	{
		return tan(x);
	}

	double derivative(double x) const override
	{
		double tangent = tan(x);
		return 1 / (pow(cos(x), 2));
	}


};