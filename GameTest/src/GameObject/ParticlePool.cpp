#include "stdafx.h"
#include "ParticlePool.h"
#include "GameObjectFactory.h"
//
#include "Component/Particle.h"
#include "Global/Utils.h"

ParticlePool::ParticlePool() {}


void ParticlePool::Init()
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		float r = Utils::RandomFloat(1.f, 10.f) / 10.f;
		float g = Utils::RandomFloat(1.f, 10.f) / 10.f;
		float b = Utils::RandomFloat(1.f, 10.f) / 10.f;
		float size = Utils::RandomFloat(3.f, 10.f) / 100.f;
		particles[i] = GameObjectFactory::CreateParticle(r, g, b, size, 50.f);
		particles[i]->Deactivate();
	}
}

void ParticlePool::Spawn(const Vector2& spawn_pos)
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

void ParticlePool::SetUp()
{
	for (const auto& particle : particles)
	{
		particle->Deactivate();
	}
}
