#pragma once

#include "Vector3f.h"
#include "Shapes.h"

#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iomanip>

std::string C[5] = { "0", "%", "o", ":", "." };

class Light
{
public:
	Vector3f position;

	Light(const Vector3f& position) : position(position) {}
};

struct Hit
{
	bool hit = false;
	Vector3f hitPosition = Vector3f();
	float hitDistance = 0.0f;
	Sphere* hitSphere;

	Hit(Vector3f hitPosition, float hitDistance, Sphere* sphere) : hitPosition(hitPosition), hitDistance(hitDistance), hit(true), hitSphere(sphere) {}
	Hit(bool hit) : hitPosition(Vector3f()), hitDistance(0.0f), hit(hit) {}
};

class Camera
{
private:
	int W = 100, H = 100;
	float VFOV = 0.52f;

public:
	Vector3f position = Vector3f(0, 0, 0);

	std::string Render(std::vector<Sphere>* spheres, Light* light)
	{
		std::string frame = "";

		for (int y = H; y > 0; --y)
		{
			for (int x = 1; x <= W - 1; ++x)
			{
				float yc = std::sin(((y - ((float)H / 2)) / (float)H) * VFOV);
				float xc = std::sin(((x - ((float)W / 2)) / (float)W) * (VFOV * (float)W / (float)H));

				Vector3f dir(xc, yc, 1);

				Hit hit = CastRay(position, dir.Normalize(), spheres);
				
				if (!hit.hit)
				{
					frame += " ";
					continue;
				}

				Vector3f relativeLight = light->position - hit.hitPosition;
				float lightDistance = relativeLight.Length();

				Hit lightHit = CastRay(hit.hitPosition, relativeLight.Normalize(), spheres);

				if (lightHit.hit)
				{
					if (lightHit.hitDistance < lightDistance)
					{
						frame += " ";
						continue;
					}
				}

				Vector3f normal = (hit.hitPosition - hit.hitSphere->position).Normalize();
				float intensity = Vector3f::Dot(relativeLight.Normalize(), normal);
				intensity = std::max(0.0f, intensity);

				if (intensity >= .8f) frame += C[0];
				else if (intensity < .8f && intensity >= .6f) frame += C[1];
				else if (intensity < .6f && intensity >= .4f) frame += C[2];
				else if (intensity < .4f && intensity >= .2f) frame += C[3];
				else if (intensity < .2f && intensity > 0.0f) frame += C[4];
				else frame += " ";
			}
			frame += "\n";
		}

		return frame;
	}

	Hit CastRay(Vector3f origin, Vector3f dir, std::vector<Sphere>* spheres)
	{
		float closestDistance = 1e10f;
		Vector3f closestHitPoint = Vector3f();
		Sphere* sphere = nullptr;

		for (int i = 0; i < spheres->size(); ++i)
		{
			Vector3f transformedPosition = origin - spheres->at(i).position;
			float determinant = Vector3f::Dot(dir, transformedPosition) * Vector3f::Dot(dir, transformedPosition) - (transformedPosition.SqrLength() - (spheres->at(i).radius * spheres->at(i).radius));
		
			if (determinant < 0) continue;

			float distance = std::min(-Vector3f::Dot(dir, transformedPosition) + std::sqrt(determinant), -Vector3f::Dot(dir, transformedPosition) - std::sqrt(determinant));

			if (distance >= closestDistance or distance < 0.00001f) continue;

			closestDistance = distance;
			
			closestHitPoint = dir * distance + origin;
			sphere = &spheres->at(i);
		}

		if (closestDistance != 1e10f)
		{
			return Hit(closestHitPoint, closestDistance, sphere);
		}
		else
		{
			return Hit(false);
		}
	}

	Camera(int WIDTH, int HEIGTH, float VerticalFOV) : W(WIDTH), H(HEIGTH), VFOV(VerticalFOV) {}
};