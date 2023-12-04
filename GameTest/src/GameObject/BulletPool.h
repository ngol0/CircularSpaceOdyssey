#pragma once
#include "GameObject.h"


class BulletPool
{
public:
	BulletPool();

	void Init();
	void Spawn(const Vector2& spawn_pos, const Vector2& direction, float rotation_angle);
	void SetUp();

private:
	static const int POOL_SIZE = 10;
	Object::Ref bullets[POOL_SIZE];
};