#pragma once
#include "GameObject.h"

enum class ParticleType;

class ParticlePool
{
public:
	ParticlePool();
	~ParticlePool() {};

	void Init(float lifespan, ParticleType type);

	void EmitToRandomDirection(const Vector2& spawn_pos);
	void EmitToDirection(const Vector2& spawn_pos, float angle);

	void SetUp();

private:
	static const int POOL_SIZE = 200;
	Object::Ref particles[POOL_SIZE];
};