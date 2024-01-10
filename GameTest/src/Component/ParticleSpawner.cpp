#include "stdafx.h"
#include "ParticleSpawner.h"
#include "GameObject/ParticlePool.h"

static const int MAX_PARTICLES = 8; //max particles to spawn each time

namespace ExplosionParticleEmitter
{
	void Emit(ParticlePool& pool, const Vector2& spawn_pos)
	{
		for (int i = 0; i < MAX_PARTICLES; i++)
		{
			pool.Spawn(spawn_pos);
		}
	}
}
