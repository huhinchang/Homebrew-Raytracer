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
extern const double infinity;
extern const double pi;

// Functions
double Deg2Rad(double degrees);
double Lerp(double a, double b, double t);
double RandomDouble(double min = 0, double max = 1); // inclusive min, exclusive max
double Clamp(double x, double min, double max);