#pragma once

// this header contains the ray class

#include "Vector3.h"

class Ray
{
public:
	Ray() {}
	Ray(const Point3& origin, const Vector3& direction)
		: _origin{ origin }, _direction{ Normalized(direction) }
	{
	}

	Point3 Origin() const { return _origin; }
	Vector3 Direction() const { return _direction; }

	Point3 At(double t) const
	{
		return _origin + t * _direction;
	}

private:
	Point3 _origin;
	Vector3 _direction;
};