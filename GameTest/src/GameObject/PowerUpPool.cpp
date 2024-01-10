#include "stdafx.h"
#include "PowerUpPool.h"
#include "GameObjectFactory.h"

PowerUpPool::PowerUpPool() {}

void PowerUpPool::Init(PowerUpType powerup_type)
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		power_ups[i] = GameObjectFactory::CreatePowerUp(powerup_type);
		power_ups[i]->Deactivate();
	}
}

void PowerUpPool::Spawn(Waypoint& spawn_pos)
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		if (!power_ups[i]->IsAlive())
		{
			power_ups[i]->SetPosition(spawn_pos.position);
			spawn_pos.is_available = false;
			power_ups[i]->Activate();

			return;
		}
	}
}

void PowerUpPool::SetUp()
{
	for (const auto& item : power_ups)
	{
		item->Deactivate();
	}
}