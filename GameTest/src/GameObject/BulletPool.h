#pragma once
#include "GameObject.h"


class BulletPool
{
public:
	BulletPool(float r, float b, float g, float size, int lifespan, float speed, std::string tag);

	void Init();
	void Spawn(const Vector2& spawn_pos, const Vector2& direction, float rotation_angle);
	void SetUp();

private:
	static const int POOL_SIZE = 10;
	Object::Ref bullets[POOL_SIZE];

	//bullet color & size & tag
	float m_r;
	float m_b;
	float m_g;
	float m_size;
	int m_lifespan;
	float m_speed;
	std::string m_tag;
};