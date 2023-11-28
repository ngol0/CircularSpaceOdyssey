#include "stdafx.h"
#include "BulletMovement.h"
#include "Transform.h"
#include "Component.h"
#include "GameObject/GameObject.h"


BulletMovement::BulletMovement() : move_direction(Vector2{0.f}), transform(nullptr), frame_left(0.f)
{
}

void BulletMovement::Init()
{
	transform = &Component::object->GetComponent<Transform>();
	frame_left = 75;
}

void BulletMovement::SetDirection(const Vector2& direction)
{
	move_direction = direction;
}

void BulletMovement::Update(float deltaTime)
{
	frame_left--;
	transform->position = transform->position + move_direction * 0.2f * deltaTime;

	if (frame_left <= 0)
	{
		Component::object->Deactivate();
	}
}
