#include "stdafx.h"
#include "EnemySpawner.h"
#include "EnemyMovement.h"
#include "Transform.h"
//
#include "GameObject/EnemyPool.h"
#include "System/Utils.h"

float EnemySpawner::MAX_SPAWN_TIME = 8.f;

EnemySpawner::EnemySpawner() : m_timer(0.f), m_pool(nullptr) {}

void EnemySpawner::SetUp(EnemyPool& pool)
{
	m_timer = MAX_SPAWN_TIME;
	m_pool = &pool;

	//init waypoints
	std::vector<Vector2> m_vertices;
	Utils::GenerateCircleVertices(distance_to_center, Component::object->GetComponent<Transform>().position, 10, m_vertices);

	for (auto& vertice : m_vertices)
	{
		m_waypoint_list.push_back(Waypoint{ vertice, true });
	}
}

void EnemySpawner::SpawnEnemy(const Vector2& spawn_pos, float rotation_angle, float dt)
{
	//check if there's available waypoints
	Waypoint* destination = GetAvailableWaypoint();

	//if no, return;
	if (destination == nullptr)
	{
		return;
	}

	//if yes, spawn enemy and move it there
	m_timer -= dt / 100.f;
	if (m_timer <= 0.f)
	{
		Object::Ref enemy = m_pool->Spawn(spawn_pos, *destination, 0.f);
		destination->is_available = false;

		m_timer = MAX_SPAWN_TIME;
	}
}

Waypoint* EnemySpawner::GetAvailableWaypoint()
{
	for (auto& waypoint : m_waypoint_list)
	{
		if (waypoint.is_available)
		{
			return &waypoint;
		}
	}
	return nullptr;
}