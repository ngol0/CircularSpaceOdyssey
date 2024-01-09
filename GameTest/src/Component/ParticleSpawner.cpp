#include "stdafx.h"
#include "ParticleSpawner.h"
#include "GameObject/ParticlePool.h"

ParticleSpawner::ParticleSpawner() {}

void ParticleSpawner::SetUp(ParticlePool& pool)
{
	m_pool = &pool;
}

void ParticleSpawner::Emit(const Vector2& spawn_pos)
{
	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		m_pool->Spawn(spawn_pos);
	}
}