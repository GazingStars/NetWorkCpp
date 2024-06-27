#pragma once
#include "ActivationFunction.h"
#include <cmath>
#include <math.h>


class Tangent : public ActivationFunctions
{
	double activate(double x)const override
	{
		return tanh(x);
	}

	double derivative(double x) const override
	{
		double epsilon = 1e-9;
		if (std::abs(x - 1.0) < epsilon || std::abs(x) < epsilon)
			return 0.0; // Если x очень близок к 1 или 0, отсечем его
	
		return 1 - x * x;
	}
};