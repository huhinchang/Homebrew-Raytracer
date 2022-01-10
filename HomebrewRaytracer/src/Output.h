#pragma once

// this header contains color helper functions

#include "Vector3.h"

#include <iostream>

void WriteColorRaw(std::ostream &out, color pixelColor)
{
	// Write the translated [0,255] value of each color component.
	out << pixelColor.x << ' '
		<< 255.999 * pixelColor.y << ' '
		<< 255.999 * pixelColor.z << '\n';
}

// multisampled color
void WriteColor(std::ostream &out, color pixelColor, int samplesPerPixel)
{
	auto r = pixelColor.x;
	auto g = pixelColor.y;
	auto b = pixelColor.z;

	// Divide the color by the number of samples and gamma-correct for gamma=2.0.
	auto scale = 1.0 / samplesPerPixel;
	r = sqrt(scale * r);
	g = sqrt(scale * g);
	b = sqrt(scale * b);

	// Write the translated [0,255] value of each color component.
	out << static_cast<int>(256 * Clamp(r, 0.0, 0.999)) << ' '
		<< static_cast<int>(256 * Clamp(g, 0.0, 0.999)) << ' '
		<< static_cast<int>(256 * Clamp(b, 0.0, 0.999)) << '\n';
}