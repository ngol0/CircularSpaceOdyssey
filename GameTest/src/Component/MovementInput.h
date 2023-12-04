#pragma once
#include "Component.h"
#include "Transform.h"

struct MovementInput : public Component
{
	MovementInput(const Vector2& center, float distance);

	void Init() override;
	void Update(float deltaTime) override;
	void SetUp();

	void UpdateTransform();

private:
	float m_speed;
	Transform* transform;
	const Vector2* m_center;

	//movement values
	float m_degree;
	float m_distance;
	float m_rotation_angle;
};