#include "stdafx.h"
#include "EnemyMovement.h"
#include "Transform.h"
#include "EnemySpawner.h"
#include "EnemyRandomMovement.h"
//
#include "GameObject/GameObject.h"

EnemyMovement::EnemyMovement(float speed) : m_speed(speed), m_waypoint_destination(nullptr), m_transform(nullptr), m_pos_destination(nullptr) {}

void EnemyMovement::Init()
{
	m_transform = &Component::object->GetComponent<Transform>();
}

void EnemyMovement::MoveTo(Waypoint& pos)
{
	m_waypoint_destination = &pos;
}

void EnemyMovement::MoveTo(const Vector2& pos)
{
	m_pos_destination = &pos;
}

void EnemyMovement::Update(float deltaTime)
{
	Vector2 move_vector;
	//move to destination
	if (m_waypoint_destination == nullptr && m_pos_destination != nullptr)
	{
		move_vector = *m_pos_destination - m_transform->position;
	}
	else if (m_waypoint_destination != nullptr && m_pos_destination == nullptr)
	{
		move_vector = m_waypoint_destination->position - m_transform->position;
	}
	float move_distance = move_vector.magnitude();
	if (move_distance <= 2.f)
	{
		//reach the destination and keep moving to the next random waypoint
		if (Component::object->HasComponent<EnemyRandomMovement>())
		{
			Component::object->GetComponent<EnemyRandomMovement>().GetNextDestination();
		}
		return;
	}

	m_transform->position = m_transform->position + move_vector.normalize() * m_speed * deltaTime;
}

void EnemyMovement::Reset()
{
	if (m_waypoint_destination == nullptr) return;
	m_waypoint_destination->is_available = true;
}