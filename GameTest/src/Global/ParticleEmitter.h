#pragma once
#include "Math/Vector2.h"

class ParticlePool;

namespace ParticleEmitter
{
	void EmitExplosion(ParticlePool& pool, const Vector2& spawn_pos);
	void EmitHealing(ParticlePool& pool, const Vector2& spawn_pos);
};