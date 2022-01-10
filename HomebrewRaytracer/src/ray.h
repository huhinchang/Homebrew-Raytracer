#pragma once

// this header contains the ray class

#include "Vector3.h"

class Ray
{
public:
	Ray() {}
	Ray(const point3& origin, const Vector3& direction)
		: _origin{ origin }, _direction{ direction }
	{
	}

	point3 origin() const { return _origin; }
	Vector3 direction() const { return _direction; }

	point3 At(double t) const
	{
		return _origin + t * _direction;
	}

public:
	point3 _origin;
	Vector3 _direction;
};