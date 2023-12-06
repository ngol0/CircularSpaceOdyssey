#pragma once
#include "Math/Vector2.h"
#include "Component.h"

class Scene;
class EnemyPool;

struct Waypoint
{
	Vector2 position;
	bool is_available;
};

class EnemySpawner : public Component
{
private:
	std::vector<Waypoint> m_waypoint_list;
	float m_timer;
	float distance_to_center = 150.f;

	EnemyPool* m_pool;

public:
	EnemySpawner();
	~EnemySpawner() {};

	void Init() override {};
	void SetUp(EnemyPool& pool);
	void Reset();

	void SpawnEnemy(const Vector2& spawn_pos, float rotation_angle, float dt);
	Waypoint* GetAvailableWaypoint();

	static float MAX_SPAWN_TIME;
};