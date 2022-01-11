#pragma once

// this header contains useful misc. functions and constants

#include <cmath>
#include <limits>
#include <memory>
#include <random>

// Usings
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Functions
inline double Deg2Rad(double degrees)
{
	return degrees * pi / 180.0;
}

inline double Lerp(double a, double b, double t)
{
	return a + (b-a) * t;
}

// inclusive min, exclusive max
inline double RandomDouble(double min = 0, double max = 1)
{
	// https://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution
	std::random_device rd;  // Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> dis(min, max);

	return dis(gen);
}

inline double Clamp(double x, double min, double max)
{
	if (x < min) return min;
	if (x > max) return max;
	return x;
}