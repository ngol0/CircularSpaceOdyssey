#pragma once
#include "Math/Vector2.h"
#include "Component.h"

struct Transform : public Component
{
	Transform();
	Transform(const Vector2& position, float scale);
	Transform(const Vector2& position, float rotation, float scale);

	Vector2 position;
	//Vector2 rotation;
	float rotation_angle;
	float scale;

	Vector2 forward;

	void Init() override;
	void Update(float deltaTime) override;
};