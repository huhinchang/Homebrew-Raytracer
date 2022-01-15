#pragma once

#include "Utils.h"

class Vector3
{
public:
	double x;
	double y;
	double z;

	Vector3();
	Vector3(double x, double y, double z);

	Vector3 operator-() const;
	Vector3& operator+=(const Vector3 &other);
	Vector3& operator*=(const double t);
	Vector3& operator/=(const double t);

	double Magnitude() const;
	double SqrMagnitude() const;

	static Vector3 Random();
	static Vector3 Random(double min, double max);
};

// Type aliases for vec3
using Point3 = Vector3;   // 3D point
using Color = Vector3;    // RGB color

// vec3 Utility Functions
Vector3 operator+(const Vector3 &u, const Vector3 &v);
Vector3 operator-(const Vector3 &u, const Vector3 &v);
Vector3 operator*(const Vector3 &u, const Vector3 &v);// doesn't make sense mathematically but useful for colors
Vector3 operator*(double t, const Vector3 &v);
Vector3 operator*(const Vector3 &v, double t);
Vector3 operator/(Vector3 v, double t);

double Dot(const Vector3 &u, const Vector3 &v);
Vector3 Cross(const Vector3 &u, const Vector3 &v);
Vector3 Lerp(const Vector3 &u, const Vector3 &v, double t);
Vector3 Normalized(Vector3 v);

Vector3 RandomInUnitSphere();
Vector3 RandomUnitVector();
Vector3 RandomInUnitDisk();

Vector3 ReflectAlongNormal(const Vector3& v, const Vector3& n);
Vector3 Refract(const Vector3& uv, const Vector3& n, double etai_over_etat); // ray tracing in one weekend 10.2 for derivation