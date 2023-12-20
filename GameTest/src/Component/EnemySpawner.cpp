#include "stdafx.h"
#include "EnemySpawner.h"
#include "EnemyMovement.h"
#include "Transform.h"
//
#include "GameObject/EnemyPool.h"
#include "System/Utils.h"


EnemySpawner::EnemySpawner() : m_pool(nullptr), m_transform(nullptr) {}

void EnemySpawner::SetUp(EnemyPool& pool, float max_spawn_time)
{
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

void EnemySpawner::SpawnEnemy(Waypoint& destination, float dt)
{
	m_pool->Spawn(m_transform->position, destination, 0.f);
	destination.is_available = false;
}

void EnemySpawner::SpawnEnemy(const Vector2& destination, float dt)
{
	m_pool->Spawn(m_transform->position, destination, 0.f);
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
	for (auto& waypoint : m_waypoint_list)
	{
		waypoint.is_available = true;
	}
}