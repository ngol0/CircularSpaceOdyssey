#include "stdafx.h"
#include "EnemySpawner.h"
#include "EnemyMovement.h"
#include "Transform.h"
//
#include "GameObject/EnemyPool.h"
#include "System/Utils.h"


EnemySpawner::EnemySpawner() : m_timer(0.f), m_max_spawn_time(0.f), m_pool(nullptr), m_transform(nullptr) {}

void EnemySpawner::SetUp(EnemyPool& pool, float max_spawn_time)
{
	m_timer = max_spawn_time;
	m_max_spawn_time = max_spawn_time;
	m_pool = &pool;
	m_transform = &Component::object->GetComponent<Transform>();
}

void EnemySpawner::InitWaypoints()
{
	//init waypoints
	std::vector<Vector2> m_vertices;
	Utils::GenerateCircleVertices(m_distance_to_center, m_transform->position, 10, m_vertices);

	for (auto& vertice : m_vertices)
	{
		m_waypoint_list.push_back(Waypoint{ vertice, true });
	}
}

void EnemySpawner::SpawnEnemyToWaypoint(float dt, float rotation_angle)
{
	//check if there's available waypoints
	Waypoint* destination = GetAvailableWaypoint();

	//if no, return;
	if (destination == nullptr)
	{
		return;
	}

	//if yes, spawn enemy and move it there
	SpawnEnemy(*destination, dt);
}

void EnemySpawner::SpawnEnemy(Waypoint& destination, float dt)
{
	//if yes, spawn enemy and move it there
	m_timer -= dt / 100.f;
	if (m_timer <= 0.f)
	{
		Object::Ref enemy = m_pool->Spawn(m_transform->position, destination, 0.f);
		destination.is_available = false;
		m_timer = m_max_spawn_time;
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

void EnemySpawner::Reset()
{
	m_timer = m_max_spawn_time;

	for (auto& waypoint : m_waypoint_list)
	{
		waypoint.is_available = true;
	}
}