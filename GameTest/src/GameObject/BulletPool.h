#pragma once
#include "GameObject.h"

class Scene;

class BulletPool
{
public:
	BulletPool();

	void Init(Scene& scene);
	void Spawn(const Vector2& spawn_pos, const Vector2& direction, float rotation_angle);

private:
	static const int POOL_SIZE = 10;
	Core::Ref bullets[POOL_SIZE];
};