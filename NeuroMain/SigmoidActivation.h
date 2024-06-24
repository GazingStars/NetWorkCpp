#pragma once
#include "ActivationFunction.h"
#include <cmath>


class SigmoidActivation : public ActivationFunctions
{
public:

	double activate(double x)const override
	{
		return 1.0 / (1.0 + std::exp(-x));
	}

	double derivative(double x) const override 
	{
		double sigmoid = activate(x);
		return sigmoid * (1 - sigmoid);
	}

};

