#pragma once
#include "Math/Vector2.h"
#include "Component.h"

class Scene;
class EnemyPool;
class Transform;

struct Waypoint
{
	Vector2 position;
	bool is_available;
};

class EnemySpawner : public Component
{
private:
	std::vector<Waypoint> m_waypoint_list;
	float m_distance_to_center = 150.f;

	EnemyPool* m_pool;
	Transform* m_transform;

public:
	EnemySpawner();
	~EnemySpawner() {};

	void Init() override {};
	void SetUp(EnemyPool& pool);
	void Reset();
	void InitWaypoints();

	void SpawnEnemy();
	void SpawnEnemy(Waypoint& destination);
	void SpawnEnemy(const Vector2& destination);
	void SpawnEnemyAtPos(const Vector2 spawn_pos, const Vector2& destination);
	Waypoint* GetAvailableWaypoint();
};