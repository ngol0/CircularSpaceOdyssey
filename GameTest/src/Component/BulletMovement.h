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

	Vector2 move_direction;
	Transform* transform;

private:
	int m_frame_left;
};