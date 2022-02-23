#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include <string>
#include <iostream>

class Vector2
{
public:
	Vector2();
	Vector2(float x, float y);
	float Magnitude() const;
	float SqrMagnitude() const;
	float DistanceTo(const Vector2& v) const;
	float SqrDistanceTo(const Vector2& v) const;
	float Dot(const Vector2& v);
	float GetAngle();
	static double DegToRad(double degrees);
	static double RadToDeg(double radians);
	Vector2 Normalize();
	std::string ToString() const;
	Vector2 Rotate(double degrees) const;

	friend Vector2 operator+(const Vector2& v1, const Vector2& v2);
	friend Vector2 operator-(const Vector2& v1, const Vector2& v2);
	friend Vector2 operator*(const double multiplier, const Vector2& v1);
	friend Vector2 operator*(const Vector2& v1, const double multiplier);
	friend bool operator<(const Vector2& v1, const Vector2& v2);
	friend bool operator>(const Vector2& v1, const Vector2& v2);

	Vector2 operator-() const; //unary operator ex: -v3;
	Vector2& operator+=(const Vector2& v2);
	Vector2& operator-=(const Vector2& v2);

	friend std::ostream& operator<< (std::ostream& out, const Vector2& v);

	static const Vector2 Up() { return Vector2(0, -1); };
	static const Vector2 Down() { return Vector2(0, 1); };
	static const Vector2 Right() { return Vector2(1, 0); };
	static const Vector2 Left() { return Vector2(-1, 0); };

	union
	{
		struct
		{
			float x;
			float y;
		};
		struct
		{
			float v[2];
		};
	};

	float operator[](const int unsigned& idx)
	{
		float* foo = (float*)this;
		return foo[idx];
	}
};


