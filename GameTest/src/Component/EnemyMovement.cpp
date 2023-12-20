#include "stdafx.h"
#include "EnemyMovement.h"
#include "Component/Transform.h"
#include "EnemySpawner.h"
//
#include "GameObject/GameObject.h"

EnemyMovement::EnemyMovement(float speed) : m_speed(speed), m_destination(nullptr), m_transform(nullptr), m_pos(nullptr) {}

void EnemyMovement::Init()
{
	m_transform = &Component::object->GetComponent<Transform>();
}

void EnemyMovement::MoveTo(Waypoint& pos)
{
	m_destination = &pos;
	std::cout << "x-2: " << m_destination->position.x << std::endl;
}

void EnemyMovement::MoveTo(const Vector2& pos)
{
	m_pos = &pos;
}

void EnemyMovement::Update(float deltaTime)
{
	Vector2 move_vector;
	//move to destination
	if (m_destination == nullptr)
	{
		move_vector = *m_pos - m_transform->position;
	}
	else
	{
		move_vector = m_destination->position - m_transform->position;
	}
	float move_distance = move_vector.magnitude();
	if (move_distance <= 2.f) return;

	m_transform->position = m_transform->position + move_vector.normalize() * m_speed * deltaTime;
}

void EnemyMovement::Reset()
{
	if (m_destination == nullptr) return;
	m_destination->is_available = true;
}