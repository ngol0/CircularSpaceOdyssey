#include "stdafx.h"
#include "EnemyMovement.h"
#include "Component/Transform.h"
#include "EnemySpawner.h"
//
#include "GameObject/GameObject.h"

EnemyMovement::EnemyMovement() : m_speed(0.f), m_destination(nullptr), m_transform(nullptr) {}

void EnemyMovement::Init()
{
	m_transform = &Component::object->GetComponent<Transform>();

	m_speed = 0.2f;
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