#pragma once
#include "Math/Vector2.h"

class ParticlePool;

namespace ExplosionParticleEmitter
{
	void Emit(ParticlePool& pool, const Vector2& spawn_pos);
};