#pragma once
#include "Math/Vector2.h"
#include "Component.h"

class Scene;
class EnemyPool;
class Transform;

class EnemySpawner : public Component
{
private:
	EnemyPool* m_pool;
	Transform* m_transform;

public:
	EnemySpawner();
	~EnemySpawner() {};

	void Init() override {};
	void SetUp(EnemyPool& pool);

	void SpawnEnemy();
	void SpawnEnemyToPos(Waypoint& destination);
	void SpawnEnemyToPos(const Vector2& destination);
	void SpawnEnemyAtPos(const Vector2& spawn_pos, const Vector2& destination);
};