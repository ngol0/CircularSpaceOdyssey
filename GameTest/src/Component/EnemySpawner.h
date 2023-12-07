#pragma once
#include "Math/Vector2.h"
#include "Component.h"

class Scene;
class EnemyPool;
struct Transform;

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
	Transform* m_transform;

public:
	EnemySpawner();
	~EnemySpawner() {};

	void Init() override {};
	void SetUp(EnemyPool& pool);
	void Reset();

	void SpawnEnemy(float rotation_angle, float dt);
	Waypoint* GetAvailableWaypoint();

	static float MAX_SPAWN_TIME;
};