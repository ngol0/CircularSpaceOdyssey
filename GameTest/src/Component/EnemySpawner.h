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
	float m_timer;
	float m_distance_to_center = 150.f;
	float m_max_spawn_time;

	EnemyPool* m_pool;
	Transform* m_transform;

public:
	EnemySpawner();
	~EnemySpawner() {};

	void Init() override {};
	void SetUp(EnemyPool& pool, float max_spawn_time);
	void Reset();
	void InitWaypoints();

	void SpawnEnemyToWaypoint(float dt = 0.f, float rotation_angle = 0.f);
	void SpawnEnemy(Waypoint& destination, float dt);
	Waypoint* GetAvailableWaypoint();
};