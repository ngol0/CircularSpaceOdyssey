#include "stdafx.h"
#include "BulletPool.h"
#include "Component/BulletMovement.h"
//
#include "GameObjectFactory.h"

BulletPool::BulletPool(float r, float b, float g, float size, int lifespan, std::string tag) : m_r(r), m_b(b), m_g(g), m_size(size), m_lifespan(lifespan), m_tag(tag) {}

void BulletPool::Init()
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		bullets[i] = GameObjectFactory::CreateBullet(m_r, m_b, m_g, m_size, m_lifespan, m_tag);
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