#pragma once

// this header contains the ray class

#include "Vector3.h"

class Ray
{
public:
	Ray() {}
	Ray(const point3& origin, const Vector3& direction)
		: _origin{ origin }, _direction{ Normalized(direction) }
	{
	}

	point3 Origin() const { return _origin; }
	Vector3 Direction() const { return _direction; }

	point3 At(double t) const
	{
		return _origin + t * _direction;
	}

private:
	point3 _origin;
	Vector3 _direction;
};