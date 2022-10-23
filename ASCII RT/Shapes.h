#pragma once

#include "Vector3f.h"

struct Sphere
{
	Vector3f position = Vector3f(0, 0, 0);
	float radius = 1.0f;

	Sphere(Vector3f position, float radius) : position(position), radius(radius) {}
};