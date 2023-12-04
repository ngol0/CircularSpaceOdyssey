#include "stdafx.h"
#include "BulletMovement.h"
#include "Transform.h"
#include "GameObject/GameObject.h"


BulletMovement::BulletMovement() : m_frame_left(0.f), m_speed(0.f), m_move_direction(Vector2{0.f}), m_transform(nullptr)
{
	
}

void BulletMovement::Init()
{
	m_transform = &Component::object->GetComponent<Transform>();
	m_frame_left = 75;
	m_speed = 0.2f;
}

void BulletMovement::SetDirection(const Vector2& direction)
{
	m_move_direction = direction;
}

void BulletMovement::Update(float deltaTime)
{
	m_frame_left--;
	m_transform->position = m_transform->position + m_move_direction * m_speed * deltaTime;

	if (m_frame_left <= 0)
	{
		Component::object->Deactivate();
	}
}

void BulletMovement::ResetLife()
{
	m_frame_left = 75;
}
