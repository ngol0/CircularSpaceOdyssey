/* Movement input component for controlling player movement
* It calculates the position degree and rotation angle for player when it moves around the circle
*/
#pragma once
#include "Component.h"
#include "Transform.h"

class MovementInput : public Component
{
public:
	MovementInput(const Vector2& center, float distance);

	void Init() override;
	void Update(float deltaTime) override;
	void SetUp();

	void UpdateTransform();

	//getter
	float GetAngle() { return m_degree * (PI / 180.f); }
	float GetAngularVelocity() { return m_angular_speed; }
	bool IsClockWise() { return m_is_clockwise; }
	float GetDistanceToCenter() { return m_distance; }
	bool IsMoving() { return m_is_moving; }

private:
	float m_speed;
	Transform* transform;
	const Vector2* m_center;

	//movement values
	float m_degree;
	float m_distance;
	float m_rotation_angle;
	bool m_is_clockwise{false};
	float m_angular_speed{ 0.f };
	bool m_is_moving{ false };
};