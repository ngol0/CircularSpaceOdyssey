#pragma once

struct Vector2
{
	Vector2();
	Vector2(float size);
	Vector2(float x, float y);

	float x;
	float y;

	Vector2 operator+(const Vector2& other) const;
	Vector2 operator-(const Vector2& other) const;
	Vector2 operator*(float scalar) const;
	Vector2 operator/(float scalar) const;
	bool operator==(const Vector2& other) const;

	Vector2 normalize() const;
	float magnitude() const;
};

struct Waypoint
{
	Vector2 position;
	bool is_available;
};