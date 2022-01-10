#pragma once

#include "Utils.h"

class Vector3
{
public:
	double x;
	double y;
	double z;

	Vector3() : x{ 0 }, y{ 0 }, z{ 0 } {}
	Vector3(double x, double y, double z) : x{ x }, y{ y }, z{ z } {}

	Vector3 operator-() const { return Vector3(-x, -y, -z); }
	//double operator[](int i) const { return e[i]; }
	//double& operator[](int i) { return e[i]; }

	Vector3& operator+=(const Vector3 &other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	Vector3& operator*=(const double t)
	{
		x *= t;
		y *= t;
		z *= t;
		return *this;
	}

	Vector3& operator/=(const double t)
	{
		return *this *= 1 / t;
	}

	double Magnitude() const
	{
		return sqrt(SqrMagnitude());
	}

	double SqrMagnitude() const
	{
		return x * x + y * y + z * z;
	}

	inline static Vector3 random()
	{
		return Vector3(RandomDouble(), RandomDouble(), RandomDouble());
	}

	inline static Vector3 random(double min, double max)
	{
		return Vector3(RandomDouble(min, max), RandomDouble(min, max), RandomDouble(min, max));
	}

	bool near_zero() const
	{
		const auto s = 1e-8;
		return (fabs(x) < s) && (fabs(y) < s) && (fabs(z) < s);
	}
};

// Type aliases for vec3
using point3 = Vector3;   // 3D point
using color = Vector3;    // RGB color

// vec3 Utility Functions
/*

inline std::ostream& operator<<(std::ostream &out, const vec3 &v)
{
	return out << v._x << ' ' << v._y << ' ' << v._z;
}
*/

inline Vector3 operator+(const Vector3 &u, const Vector3 &v)
{
	return Vector3(u.x + v.x, u.y + v.y, u.z + v.z);
}

inline Vector3 operator-(const Vector3 &u, const Vector3 &v)
{
	return Vector3(u.x - v.x, u.y - v.y, u.z - v.z);
}

// doesn't make sense mathematically but useful for colors
inline Vector3 operator*(const Vector3 &u, const Vector3 &v)
{
	return Vector3(u.x * v.x, u.y * v.y, u.z * v.z);
}

inline Vector3 operator*(double t, const Vector3 &v)
{
	return Vector3(t*v.x, t*v.y, t*v.z);
}

inline Vector3 operator*(const Vector3 &v, double t)
{
	return t * v;
}

inline Vector3 operator/(Vector3 v, double t)
{
	return (1 / t) * v;
}

inline double Dot(const Vector3 &u, const Vector3 &v)
{
	return u.x * v.x
		+ u.y * v.y
		+ u.z * v.z;
}

inline Vector3 Cross(const Vector3 &u, const Vector3 &v)
{
	return Vector3(u.y * v.z - u.z * v.y,
		u.z * v.x - u.x * v.z,
		u.x * v.y - u.y * v.x);
}

inline Vector3 Normalized(Vector3 v)
{
	return v / v.Magnitude();
}

Vector3 RandomInUnitSphere()
{
	while (true)
	{
		auto p = Vector3::random(-1, 1);
		if (p.SqrMagnitude() >= 1) continue;
		return p;
	}
}

Vector3 RandomUnitVector()
{
	return Normalized(RandomInUnitSphere());
}

/*
vec3 random_in_hemisphere(const vec3& normal)
{
	vec3 in_unit_sphere = RandomInUnitSphere();
	if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
		return in_unit_sphere;
	else
		return -in_unit_sphere;
}
*/

Vector3 reflect(const Vector3& v, const Vector3& n)
{
	return v - 2 * Dot(v, n)*n;
}

// ray tracing in one weekend 10.2 for derivation
Vector3 refract(const Vector3& uv, const Vector3& n, double etai_over_etat)
{
	auto cos_theta = fmin(Dot(-uv, n), 1.0);
	Vector3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
	Vector3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.SqrMagnitude())) * n;
	return r_out_perp + r_out_parallel;
}

Vector3 random_in_unit_disk()
{
	while (true)
	{
		auto p = Vector3(RandomDouble(-1, 1), RandomDouble(-1, 1), 0);
		if (p.SqrMagnitude() >= 1) continue;
		return p;
	}
}