#pragma once
#include <iostream>
#include <vector>

namespace EppMath
{
	double sigmoidSmooth(double p_value,double p_smoothness,double p_min,double p_max);
	double mean(std::vector<double> p_values);
	double stdDeviation(std::vector<double> p_values, double p_mean);
}
