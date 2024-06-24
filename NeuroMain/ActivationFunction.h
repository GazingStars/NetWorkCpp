#pragma once


class ActivationFunctions
{
public:
	virtual ~ActivationFunctions() {}
	virtual double activate(double x) const = 0;
	virtual double derivative(double x) const = 0;
};