#pragma once

// For our program the material needs to do two things:
// 1. Produce a scattered ray(or say it absorbed the incident ray).
// 2. If scattered, say how much the ray should be attenuated.

#include "Utils.h"

struct RaycastHit;

class Material
{
public:
	// if false, ray was absorbed.
	virtual bool Scatter(const Ray& incidentRay, const RaycastHit& incidentRayHitInfo, color& albedo, Ray& scattered) const = 0;
};

class Diffuse : public Material
{
public:
	Diffuse(const color& albedo) : _albedo{ albedo } {}

	virtual bool Scatter(const Ray& incidentRay, const RaycastHit& incidentRayHitInfo, color& albedo, Ray& scattered) const override
	{
		auto scatterDir = incidentRayHitInfo.Normal + RandomUnitVector();
		if (scatterDir.SqrMagnitude() < 1e-4)
			scatterDir = incidentRayHitInfo.Normal;

		scattered = Ray(incidentRayHitInfo.Point, scatterDir);
		albedo = _albedo;
		return true;
	}

public:
	color _albedo;
};

class Metal : public Material
{
public:
	Metal(const color& albedo, double roughness) : _albedo{ albedo }, _roughness{ Clamp(roughness, 0, 1) } {}

	virtual bool Scatter(
		const Ray& incidentRay, const RaycastHit& incidentRayHitInfo, color& albedo, Ray& scattered
	) const override
	{
		auto reflected = ReflectAlongNormal(Normalized(incidentRay.Direction()), incidentRayHitInfo.Normal);
		scattered = Ray(incidentRayHitInfo.Point, reflected + _roughness * RandomInUnitSphere());
		albedo = _albedo;

		// if scattered ray is below surface, absorb
		return (Dot(scattered.Direction(), incidentRayHitInfo.Normal) > 0);
	}

private:
	color _albedo;
	double _roughness;
};

class Glass : public Material
{
public:
	Glass(double ior, color albedo = color(1.0, 1.0, 1.0)) : _ior(ior), _albedo{ albedo } {}

	virtual bool Scatter(
		const Ray& incidentRay, const RaycastHit& incidentRayHitInfo, color& albedo, Ray& scattered
	) const override
	{
		albedo = _albedo;
		double refractionRatio = incidentRayHitInfo.IsNormalOutward ? (1.0 / _ior) : _ior;

		Vector3 unit_direction = incidentRay.Direction();
		double cos_theta = fmin(Dot(-unit_direction, incidentRayHitInfo.Normal), 1.0);
		double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

		bool cannot_refract = refractionRatio * sin_theta > 1.0;
		Vector3 direction;

		if (cannot_refract || reflectance(cos_theta, refractionRatio) > RandomDouble())
			direction = ReflectAlongNormal(unit_direction, incidentRayHitInfo.Normal);
		else
			direction = Refract(unit_direction, incidentRayHitInfo.Normal, refractionRatio);

		scattered = Ray(incidentRayHitInfo.Point, direction);
		return true;
	}

private:
	color _albedo;
	double _ior; // Index of Refraction

	static double reflectance(double cosine, double ref_idx)
	{
		// Use Schlick's approximation for reflectance.
		auto r0 = (1 - ref_idx) / (1 + ref_idx);
		r0 = r0 * r0;
		return r0 + (1 - r0)*pow((1 - cosine), 5);
	}
};

class Fog : public Material
{
public:
	Fog(const color& albedo) : _albedo{ albedo } {}

	virtual bool Scatter(
		const Ray& incidentRay, const RaycastHit& incidentRayHitInfo, color& albedo, Ray& scattered
	) const override
	{
	if (RandomDouble() )
		scattered = Ray(incidentRayHitInfo.Point, RandomInUnitSphere());
		albedo = _albedo;
		return true;
	}

private:
	color _albedo;
};