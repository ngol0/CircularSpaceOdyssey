#include "stdafx.h"
#include "Transform.h"


Transform::Transform() : position(Vector2{ 0.f }), rotation_angle(0.f), scale(1.f), forward(Vector2(0.f, 1.f))
{
	name = "Transform";
}

Transform::Transform(const Vector2& position, float scale) : position(position), rotation_angle(0.f), scale(scale), forward(Vector2(0.f, 1.f))
{
	name = "Transform";
}

Transform::Transform(const Vector2& position, float rotation, float scale) : position(position), rotation_angle(rotation), scale(scale), forward(Vector2(0.f, 1.f))
{
	name = "Transform";
}

void Transform::Init()
{
	
}

void Transform::Update(float deltaTime)
{

}