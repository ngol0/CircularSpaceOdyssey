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
	Object::Ref Spawn(const Vector2& spawn_pos, Waypoint& destination);
	Object::Ref Spawn(const Vector2& spawn_pos, const Vector2& destination);
	Object::Ref Spawn(const Vector2& spawn_pos);
	void SetUp();

private:
	static const int POOL_SIZE = 10;
	Object::Ref enemies[POOL_SIZE];
};
