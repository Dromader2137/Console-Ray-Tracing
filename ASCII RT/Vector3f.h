#pragma once

#include <iostream>
#include <iomanip>

struct Vector3f
{
	float x, y, z;

	Vector3f& operator+=(Vector3f rhs)
	{
		*this = *this + rhs;
		return *this;
	}
	Vector3f& operator-=(Vector3f rhs)
	{
		*this = *this - rhs;
		return *this;
	}
	Vector3f& operator*=(Vector3f rhs)
	{
		*this = *this * rhs;
		return *this;
	}
	Vector3f& operator/=(Vector3f rhs)
	{
		*this = *this / rhs;
		return *this;
	}
	Vector3f& operator*=(float rhs)
	{
		*this = *this * rhs;
		return *this;
	}
	Vector3f& operator/=(float rhs)
	{
		*this = *this / rhs;
		return *this;
	}
	friend Vector3f operator+(Vector3f lhs, Vector3f rhs)
	{
		return Vector3f(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
	}
	friend Vector3f operator-(Vector3f lhs, Vector3f rhs)
	{
		return Vector3f(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
	}
	friend Vector3f operator*(Vector3f lhs, Vector3f rhs)
	{
		return Vector3f(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
	}
	friend Vector3f operator/(Vector3f lhs, Vector3f rhs)
	{
		return Vector3f(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
	}
	friend Vector3f operator*(Vector3f lhs, float rhs)
	{
		return Vector3f(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
	}
	friend Vector3f operator/(Vector3f lhs, float rhs)
	{
		return Vector3f(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
	}
	friend bool operator==(Vector3f lhs, Vector3f rhs)
	{
		return (lhs.x == rhs.x) and (lhs.y == rhs.y) and (lhs.z == rhs.z);
	}
	friend bool operator!=(Vector3f lhs, Vector3f rhs)
	{
		return !(lhs == rhs);
	}

	Vector3f Normalize()
	{
		return *this / sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
	}
	float Length()
	{
		return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
	}
	float SqrLength()
	{
		return this->x * this->x + this->y * this->y + this->z * this->z;
	}

	static float Dot(Vector3f a, Vector3f b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}
	static Vector3f Cross(Vector3f a, Vector3f b)
	{
		Vector3f vec;
		vec.x = a.y * b.z - a.z * b.y;
		vec.y = a.z * b.x - a.x * b.z;
		vec.z = a.x * b.y - a.y * b.x;
		return vec;
	}

	Vector3f(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Vector3f()
	{
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
	}
	~Vector3f() {}

	friend std::ostream& operator<<(std::ostream& os, Vector3f vec)
	{
		os << "{ " << std::fixed << std::setprecision(1) << vec.x << " " << vec.y << " " << vec.z << " }";
		return os;
	}
	friend std::istream& operator>>(std::istream& is, Vector3f vec)
	{
		is >> vec.x >> vec.y >> vec.z;
		return is;
	}
};