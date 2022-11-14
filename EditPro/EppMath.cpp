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