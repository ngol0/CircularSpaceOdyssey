#include "stdafx.h"
#include "Vector2.h"

Vector2::Vector2() : x(0.f), y(0.f) {}
Vector2::Vector2(float size) : x(size), y(size) {}
Vector2::Vector2(float x, float y) : x(x), y(y) {}

Vector2 Vector2::operator+(const Vector2& other) const 
{
    return { x + other.x, y + other.y };
}

Vector2 Vector2::operator-(const Vector2& other) const 
{
    return { x - other.x, y - other.y };
}

Vector2 Vector2::operator*(float scalar) const 
{
    return { x * scalar, y * scalar };
}

Vector2 Vector2::operator/(float scalar) const
{
    return { x / scalar, y / scalar };
}

Vector2 Vector2::normalize() const
{
    float magnitude = sqrt(this->x * this->x + this->y * this->y);
    return *this / magnitude;
}