#include "stdafx.h"
#include "EnemySpawner.h"
#include "Transform.h"
//
#include "GameObject/EnemyPool.h"


EnemySpawner::EnemySpawner() : m_pool(nullptr), m_transform(nullptr) {}

void EnemySpawner::SetUp(EnemyPool& pool)
{
	m_pool = &pool;
	m_transform = &Component::object->GetComponent<Transform>();
}

void EnemySpawner::SpawnEnemy()
{
	m_pool->Spawn(m_transform->position, 0.f);
}

void EnemySpawner::SpawnEnemyToPos(Waypoint& destination)
{
	m_pool->Spawn(m_transform->position, destination, 0.f);
	destination.is_available = false;
}

void EnemySpawner::SpawnEnemyToPos(const Vector2& destination)
{
	m_pool->Spawn(m_transform->position, destination, 0.f);
}

void EnemySpawner::SpawnEnemyAtPos(const Vector2 spawn_pos, const Vector2& destination)
{
	m_pool->Spawn(spawn_pos, destination, 0.f);
}

void EnemySpawner::Reset()
{
	for (auto& waypoint : m_waypoint_list)
	{
		waypoint.is_available = true;
	}
}