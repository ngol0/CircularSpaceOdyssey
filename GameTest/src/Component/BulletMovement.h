#pragma once
#include "Component.h"
#include "Math/Vector2.h"

struct Transform;

struct BulletMovement : public Component
{
	BulletMovement();

	void Init() override;
	void SetDirection(const Vector2& direction);
	void Update(float deltaTime) override;
	void ResetLife();

private:
	int m_frame_left;
	float m_speed;
	Vector2 m_move_direction;
	Transform* m_transform;
};