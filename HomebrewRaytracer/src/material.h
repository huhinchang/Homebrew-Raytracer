#pragma once

// For our program the material needs to do two things:
// 1. Produce a scattered ray(or say it absorbed the incident ray).
// 2. If scattered, say how much the ray should be attenuated.

#include "Utils.h"

struct RaycastHit;

class material
{
public:
	virtual bool scatter(const Ray& r_in, const RaycastHit& rec, color& attenuation, Ray& scattered) const = 0;
};

class lambertian : public material
{
public:
	lambertian(const color& a) : albedo(a) {}

	virtual bool scatter(const Ray& r_in, const RaycastHit& rec, color& attenuation, Ray& scattered) const override
	{
		auto scatter_direction = rec.Normal + RandomUnitVector();

		// Catch degenerate scatter direction
		if (scatter_direction.near_zero())
			scatter_direction = rec.Normal;

		scattered = Ray(rec.Point, scatter_direction);
		attenuation = albedo;
		return true;
	}

public:
	color albedo;
};

class metal : public material
{
public:
	metal(const color& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

	virtual bool scatter(
		const Ray& r_in, const RaycastHit& rec, color& attenuation, Ray& scattered
	) const override
	{
		Vector3 reflected = reflect(Normalized(r_in.Direction()), rec.Normal);
		scattered = Ray(rec.Point, reflected + fuzz * RandomInUnitSphere());
		attenuation = albedo;
		return (Dot(scattered.Direction(), rec.Normal) > 0);
	}

public:
	color albedo;
	double fuzz;
};

class dielectric : public material
{
public:
	dielectric(double index_of_refraction) : ir(index_of_refraction) {}

	virtual bool scatter(
		const Ray& r_in, const RaycastHit& rec, color& attenuation, Ray& scattered
	) const override
	{
		attenuation = color(1.0, 1.0, 1.0);
		double refraction_ratio = rec.IsNormalOutward ? (1.0 / ir) : ir;

		Vector3 unit_direction = Normalized(r_in.Direction());
		double cos_theta = fmin(Dot(-unit_direction, rec.Normal), 1.0);
		double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

		bool cannot_refract = refraction_ratio * sin_theta > 1.0;
		Vector3 direction;

		if (cannot_refract || reflectance(cos_theta, refraction_ratio) > RandomDouble())
			direction = reflect(unit_direction, rec.Normal);
		else
			direction = refract(unit_direction, rec.Normal, refraction_ratio);

		scattered = Ray(rec.Point, direction);
		return true;
	}

public:
	double ir; // Index of Refraction

private:
	static double reflectance(double cosine, double ref_idx)
	{
		// Use Schlick's approximation for reflectance.
		auto r0 = (1 - ref_idx) / (1 + ref_idx);
		r0 = r0 * r0;
		return r0 + (1 - r0)*pow((1 - cosine), 5);
	}
};