/* Manages the position, scale, rotation and forward vector of the object */
#pragma once
#include "Math/Vector2.h"
#include "Component.h"

class Transform : public Component
{
public:
	Transform();
	Transform(const Vector2& position, float scale);
	Transform(const Vector2& position, float rotation, float scale);

	Vector2 position;
	float rotation_angle;
	float scale;
	Vector2 forward;

	void Init() override;
	void Update(float deltaTime) override;
};