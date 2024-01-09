#pragma once
#include "Component.h"
#include "Math/Vector2.h"

class ParticlePool;

class ParticleSpawner : public Component
{
private:
	ParticlePool* m_pool{ nullptr };

public:
	ParticleSpawner();
	~ParticleSpawner() {};

	void Init() override {};
	void SetUp(ParticlePool& pool);

	void Emit(const Vector2& spawn_pos);

	static const int MAX_PARTICLES = 8; //max particles to spawn each time
};