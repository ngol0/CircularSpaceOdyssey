#pragma once
#include "GameObject.h"

class ParticlePool
{
public:
	ParticlePool();

	void Init();
	void Emit(const Vector2& spawn_pos);
	void SetUp();

private:
	static const int POOL_SIZE = 200;
	Object::Ref particles[POOL_SIZE];
};