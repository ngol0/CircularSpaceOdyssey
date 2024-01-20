#pragma once
#include "Math/Vector2.h"
#include "Component.h"
#include "GameObject/GameObject.h"

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

	Object::Ref SpawnEnemy();
	Object::Ref SpawnEnemyToPos(Waypoint& destination);
	Object::Ref SpawnEnemyToPos(const Vector2& destination);
	Object::Ref SpawnEnemyAtPos(const Vector2& spawn_pos, const Vector2& destination);
};