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

Object::Ref EnemySpawner::SpawnEnemy()
{
	return m_pool->Spawn(m_transform->position);
}

Object::Ref EnemySpawner::SpawnEnemyToPos(Waypoint& destination)
{
	destination.is_available = false;
	return m_pool->Spawn(m_transform->position, destination);
}

Object::Ref EnemySpawner::SpawnEnemyToPos(const Vector2& destination)
{
	return m_pool->Spawn(m_transform->position, destination);
}

Object::Ref EnemySpawner::SpawnEnemyAtPos(const Vector2& spawn_pos, const Vector2& destination)
{
	return m_pool->Spawn(spawn_pos, destination);
}