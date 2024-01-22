#include "stdafx.h"
#include "ParticleEmitter.h"
#include "GameObject/ParticlePool.h"

namespace ParticleEmitter
{
	void EmitExplosion(ParticlePool& pool, const Vector2& spawn_pos)
	{
		for (int i = 0; i < 8; i++)
		{
			pool.EmitToRandomDirection(spawn_pos);
		}
	}

	void EmitHealing(ParticlePool& pool, const Vector2& spawn_pos)
	{
		for (int i = 0; i < 3; i++)
		{
			pool.EmitToDirection(spawn_pos + Vector2(10.f*i), 90.f);
		}
	}
}
