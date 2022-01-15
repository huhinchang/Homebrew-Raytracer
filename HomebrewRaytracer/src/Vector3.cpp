#include "Vector3.h"

Vector3::Vector3() : x{ 0 }, y{ 0 }, z{ 0 } {}
Vector3::Vector3(double x, double y, double z) : x{ x }, y{ y }, z{ z } {}

Vector3 Vector3::operator-() const { return Vector3(-x, -y, -z); }

Vector3& Vector3::Vector3::operator+=(const Vector3 &other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

Vector3& Vector3::operator*=(const double t)
{
	x *= t;
	y *= t;
	z *= t;
	return *this;
}

Vector3& Vector3::operator/=(const double t)
{
	return *this *= 1 / t;
}

double Vector3::Magnitude() const
{
	return sqrt(SqrMagnitude());
}

double Vector3::SqrMagnitude() const
{
	return x * x + y * y + z * z;
}

Vector3 Vector3::Random()
{
	return Vector3(RandomDouble(), RandomDouble(), RandomDouble());
}

Vector3 Vector3::Random(double min, double max)
{
	return Vector3(RandomDouble(min, max), RandomDouble(min, max), RandomDouble(min, max));
}

// vec3 Utility Functions
Vector3 operator+(const Vector3 &u, const Vector3 &v)
{
	return Vector3(u.x + v.x, u.y + v.y, u.z + v.z);
}

Vector3 operator-(const Vector3 &u, const Vector3 &v)
{
	return Vector3(u.x - v.x, u.y - v.y, u.z - v.z);
}

// doesn't make sense mathematically but useful for colors
Vector3 operator*(const Vector3 &u, const Vector3 &v)
{
	return Vector3(u.x * v.x, u.y * v.y, u.z * v.z);
}

Vector3 operator*(double t, const Vector3 &v)
{
	return Vector3(t*v.x, t*v.y, t*v.z);
}

Vector3 operator*(const Vector3 &v, double t)
{
	return t * v;
}

Vector3 operator/(Vector3 v, double t)
{
	return (1 / t) * v;
}

double Dot(const Vector3 &u, const Vector3 &v)
{
	return u.x * v.x
		+ u.y * v.y
		+ u.z * v.z;
}

Vector3 Cross(const Vector3 &u, const Vector3 &v)
{
	return Vector3(u.y * v.z - u.z * v.y,
		u.z * v.x - u.x * v.z,
		u.x * v.y - u.y * v.x);
}

Vector3 Lerp(const Vector3 &u, const Vector3 &v, double t)
{
	return Vector3(Lerp(u.x, v.x, t),
		Lerp(u.y, v.y, t),
		Lerp(u.z, v.z, t));
}

inline Vector3 Normalized(Vector3 v)
{
	return v / v.Magnitude();
}

Vector3 RandomInUnitSphere()
{
	while (true)
	{
		auto p = Vector3::Random(-1, 1);
		if (p.SqrMagnitude() >= 1) continue;
		return p;
	}
}

Vector3 RandomUnitVector()
{
	return Normalized(RandomInUnitSphere());
}

Vector3 ReflectAlongNormal(const Vector3& v, const Vector3& n)
{
	return v - 2 * Dot(v, n)*n;
}

// ray tracing in one weekend 10.2 for derivation
Vector3 Refract(const Vector3& uv, const Vector3& n, double etai_over_etat)
{
	auto cos_theta = fmin(Dot(-uv, n), 1.0);
	Vector3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
	Vector3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.SqrMagnitude())) * n;
	return r_out_perp + r_out_parallel;
}

Vector3 RandomInUnitDisk()
{
	while (true)
	{
		auto p = Vector3(RandomDouble(-1, 1), RandomDouble(-1, 1), 0);
		if (p.SqrMagnitude() >= 1) continue;
		return p;
	}
}