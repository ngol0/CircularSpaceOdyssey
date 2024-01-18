#include "stdafx.h"
#include "ParticlePool.h"
#include "GameObjectFactory.h"
//
#include "Component/Particle.h"
#include "Global/Utils.h"
#include "Global/ParticleType.h"

ParticlePool::ParticlePool() {}

void ParticlePool::Init(float lifespan, ParticleType type)
{
	float r, g, b, size;

	if (type == ParticleType::Explosion)
	{
		for (int i = 0; i < POOL_SIZE; i++)
		{
			r = Utils::RandomFloat(1.f, 10.f) / 10.f;
			g = Utils::RandomFloat(1.f, 10.f) / 10.f;
			b = Utils::RandomFloat(1.f, 10.f) / 10.f;
			size = Utils::RandomFloat(5.f, 20.f) / 100.f;
			particles[i] = GameObjectFactory::CreateParticle(r, g, b, size, lifespan, type);
			particles[i]->Deactivate();
		}
	}
	else if (type == ParticleType::Healing)
	{
		//color green
		r = 0.2f; g = 1.f; b = 0.2f;
		for (int i = 0; i < POOL_SIZE; i++)
		{
			size = Utils::RandomFloat(10.f, 30.f) / 1000.f;
			particles[i] = GameObjectFactory::CreateParticle(r, g, b, size, lifespan, type);
			particles[i]->Deactivate();
		}
	}
}

void ParticlePool::EmitToRandomDirection(const Vector2& spawn_pos)
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		if (!particles[i]->IsAlive())
		{
			particles[i]->SetPosition(spawn_pos);
			particles[i]->GetComponent<Particle>().SetDirection(Utils::RandomFloat(0.f, 360.f));
			particles[i]->GetComponent<Particle>().ResetLife(); //reset lifetime
			particles[i]->Activate();

			return;
		}
	}
}

void ParticlePool::EmitToDirection(const Vector2& spawn_pos, float angle)
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		if (!particles[i]->IsAlive())
		{
			particles[i]->SetPosition(spawn_pos);
			particles[i]->GetComponent<Particle>().SetDirection(angle);
			particles[i]->GetComponent<Particle>().ResetLife(); //reset lifetime
			particles[i]->Activate();

			return;
		}
	}
}

void ParticlePool::SetUp()
{
	for (const auto& particle : particles)
	{
		particle->Deactivate();
	}
}
