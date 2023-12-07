#pragma once
#include "GameObject.h"

class Scene;
struct Waypoint;

class EnemyPool
{
public:
	EnemyPool();

	void Init(Transform& transform, Scene& scene);
	Object::Ref Spawn(const Vector2& spawn_pos, Waypoint& destination, float rotation_angle);
	void SetUp();

private:
	static const int POOL_SIZE = 6;
	Object::Ref enemies[POOL_SIZE];
};
