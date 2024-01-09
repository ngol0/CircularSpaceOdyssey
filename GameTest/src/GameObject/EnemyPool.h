#pragma once
#include "GameObject.h"

class Scene;
struct Waypoint;
enum class EnemyType;

class EnemyPool
{
public:
	EnemyPool();

	void Init(Transform& transform, EnemyType enemy_type, Scene& scene);
	void Spawn(const Vector2& spawn_pos, Waypoint& destination, float rotation_angle);
	void Spawn(const Vector2& spawn_pos, const Vector2& destination, float rotation_angle);
	void Spawn(const Vector2& spawn_pos, float rotation_angle);
	void SetUp();

private:
	static const int POOL_SIZE = 10;
	Object::Ref enemies[POOL_SIZE];
};
