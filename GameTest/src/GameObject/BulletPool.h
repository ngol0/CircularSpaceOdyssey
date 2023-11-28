#pragma once
#include "GameObject.h"

class Scene;

class BulletPool
{
public:
	BulletPool();

	void Init(Scene& scene);
	void Spawn(const Vector2& spawn_pos, const Vector2& direction, float rotation_angle);
	void Update(float deltaTime);
	void Render();
	void Restart();

private:
	static const int POOL_SIZE = 10;
	GameObject bullets[POOL_SIZE];
};