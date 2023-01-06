#pragma once
#include <cmath>

inline float Random01()
{
	return float(rand() / (RAND_MAX + 1.0));
}

inline float RandomInRange(float min, float max)
{
	return min + (max - min) * Random01();
}

inline int RandomInRange(int min, int max)
{
	return int(min + (max - min) * Random01());
}