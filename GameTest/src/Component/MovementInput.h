#pragma once
#include "Component.h"
#include "Transform.h"

struct MovementInput : public Component
{
	MovementInput();

	void Init() override;
	void Update(float deltaTime) override;
	void Restart();
	void SetMovementValue(const Vector2& center, float distance);

private:
	float m_speed;
	Transform* transform;

	//movement values
	float m_degree = 270.0f; //starting point in the circle
	Vector2 m_center;
	float m_distance;

	float m_rotation_angle;
};