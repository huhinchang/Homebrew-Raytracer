#include <iostream>

#include "Utils.h"

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "RaycastCollider.h"
#include "material.h"

// cd "C:\Users\user\Desktop\Other devs\HomebrewRaytracer\Debug"
// "HomebrewRaytracer.exe" > ../Renders/asdf.ppm

color ray_color(const Ray& r, const RaycastCollider& world, int depth)
{
	RaycastHit rec;

	// If we've exceeded the ray bounce limit, no more light is gathered.
	if (depth <= 0)
		return color(0, 0, 0);

	// sphere intersection
	if (world.CheckCollision(r, 0.001, infinity, rec))
	{
		Ray scattered;
		color attenuation;
		if (rec.Material->Scatter(r, rec, attenuation, scattered))
			return attenuation * ray_color(scattered, world, depth - 1);
		return color(0, 0, 0);
	}

	// background
	Vector3 unit_direction = Normalized(r.Direction());
	auto t = 0.5*(unit_direction.y + 1.0);
	return (1.0 - t)*color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

hittable_list random_scene()
{
	hittable_list world;

	auto ground_material = make_shared<Diffuse>(color(0.5, 0.5, 0.5));
	world.add(make_shared<Sphere>(point3(0, -1000, 0), 1000, ground_material));

	for (int a = -2; a < 2; a++)
	{
		for (int b = -2; b < 2; b++)
		{
			auto choose_mat = RandomDouble();
			point3 center(a + 0.9*RandomDouble(), 0.2, b + 0.9*RandomDouble());

			if ((center - point3(4, 0.2, 0)).Magnitude() > 0.9)
			{
				shared_ptr<Material> sphere_material;

				if (choose_mat < 0.8)
				{
					// diffuse
					auto albedo = color::Random() * color::Random();
					sphere_material = make_shared<Diffuse>(albedo);
					world.add(make_shared<Sphere>(center, 0.2, sphere_material));
				}
				else if (choose_mat < 0.95)
				{
					// metal
					auto albedo = color::Random(0.5, 1);
					auto fuzz = RandomDouble(0, 0.5);
					sphere_material = make_shared<Metal>(albedo, fuzz);
					world.add(make_shared<Sphere>(center, 0.2, sphere_material));
				}
				else
				{
					// glass
					sphere_material = make_shared<Glass>(1.5);
					world.add(make_shared<Sphere>(center, 0.2, sphere_material));
				}
			}
		}
	}

	auto glassMat = make_shared<Glass>(1.5, color(1, 0, 0));
	auto diffuseMat = make_shared<Diffuse>(color(0.4, 0.2, 0.1));
	auto metalMat = make_shared<Metal>(color(0.7, 0.6, 0.5), 0.0);

	world.add(make_shared<Sphere>(point3(-4, 1, 0), 1.0, diffuseMat));
	world.add(make_shared<Sphere>(point3(0, 1, 0), 1.0, metalMat));
	world.add(make_shared<Sphere>(point3(4, 1, 0), 1.0, glassMat));

	return world;
}

int main()
{
	// Image
	const auto aspect_ratio = 3.0 / 2.0;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int samples_per_pixel = 1;
	const int max_depth = 5;

	// World
	auto world = random_scene();

	// Camera
	point3 lookfrom(13, 2, 3);
	point3 lookat(0, 0, 0);
	Vector3 vup(0, 1, 0);
	auto dist_to_focus = 10.0;
	auto aperture = 0.1;

	camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

	// Render

	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; --j)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < image_width; ++i)
		{
			color pixel_color(0, 0, 0);
			for (int s = 0; s < samples_per_pixel; ++s)
			{
				// u & v are random positions within the pixel
				auto u = (i + RandomDouble()) / (image_width - 1);
				auto v = (j + RandomDouble()) / (image_height - 1);
				Ray r = cam.get_ray(u, v);
				pixel_color += ray_color(r, world, max_depth);
			}
			write_color(std::cout, pixel_color, samples_per_pixel);
		}
	}
	std::cerr << "\nDone.\n";
}