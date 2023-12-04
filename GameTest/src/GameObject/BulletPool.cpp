#include "stdafx.h"
#include "BulletPool.h"
#include "Component/BulletMovement.h"
#include "Component/Transform.h"
//
#include "GameObjectFactory.h"

BulletPool::BulletPool() {}

void BulletPool::Init()
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		bullets[i] = GameObjectFactory::CreateBullet();
		bullets[i]->Deactivate();
	}
}

void BulletPool::Spawn(const Vector2& spawn_pos, const Vector2& direction, float rotation_angle)
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		if (!bullets[i]->IsAlive())
		{
			bullets[i]->SetPosition(spawn_pos);
			bullets[i]->SetRotationAngle(rotation_angle);
			bullets[i]->GetComponent<BulletMovement>().SetDirection(direction);
			bullets[i]->GetComponent<BulletMovement>().ResetLife(); //reset lifetime
			bullets[i]->Activate();

			return;
		}
	}
}

void BulletPool::SetUp()
{
	for (const auto& bullet : bullets)
	{
		bullet->Deactivate();
	}
}