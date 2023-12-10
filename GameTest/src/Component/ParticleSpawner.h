#pragma once
#include "Component.h"
#include "Math/Vector2.h"

class ParticlePool;

class ParticleSpawner : public Component
{
private:
	float m_timer;

	ParticlePool* m_pool;

public:
	ParticleSpawner();
	~ParticleSpawner() {};

	void Init() override {};
	void SetUp(ParticlePool& pool);
	void Reset();

	void Spawn(const Vector2& spawn_pos, float rotation_angle, float dt);

	static const int MAX_PARTICLES = 5; //max particles to spawn each time
};