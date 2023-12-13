#include "stdafx.h"
#include "EnemyMovement.h"
#include "Component/Transform.h"
#include "EnemySpawner.h"
//
#include "GameObject/GameObject.h"

EnemyMovement::EnemyMovement(float speed) : m_speed(speed), m_destination(nullptr), m_transform(nullptr) {}

void EnemyMovement::Init()
{
	m_transform = &Component::object->GetComponent<Transform>();
}

void EnemyMovement::MoveTo(Waypoint& pos)
{
	m_destination = &pos;
}

void EnemyMovement::Update(float deltaTime)
{
	//move to destination
	Vector2 move_vector = m_destination->position - m_transform->position;
	float move_distance = move_vector.magnitude();
	if (move_distance <= 2.f) return;

	m_transform->position = m_transform->position + move_vector.normalize() * m_speed * deltaTime;
}

void EnemyMovement::Reset()
{
	m_destination->is_available = true;
}