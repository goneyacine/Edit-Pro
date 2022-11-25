#include "EppMath.h"
#include <iostream>
using namespace EppMath;


double EppMath::sigmoidSmooth(double p_value, double p_smoothness, double p_min, double p_max)
{
	double output = 1 / (1 + exp(-(p_value / (p_max - p_min) * p_smoothness - (p_smoothness / 2)))) * (p_max - p_min) + p_min - (2 * p_smoothness);

	if (output > p_max)
		return p_max;
	else if (output < p_min)
		return p_min;
	else
		return output;
}

double EppMath::mean(std::vector<double> p_values)
{
	double mean = 0;
	for (auto value : p_values)
	{
		mean += value;
	}
	mean = mean / p_values.size();

	return mean;
}

double EppMath::stdDeviation(std::vector<double> p_values, double p_mean)
{
	double deviation = 0;
	for (auto value : p_values)
	{
		deviation += std::pow(value - p_mean, 2);
	}
	deviation = deviation / p_values.size();

	return deviation;
}