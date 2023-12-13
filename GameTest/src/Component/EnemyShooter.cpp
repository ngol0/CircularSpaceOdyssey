#include "stdafx.h"
#include "EnemyShooter.h"
#include "Component/Transform.h"

EnemyShooter::EnemyShooter(float offset) : m_timer(0.f), m_spawn_offset(offset), m_shooter_transform(nullptr)
{
	bullet_pool.Init();
}

void EnemyShooter::Init()
{
	m_shooter_transform = &Component::object->GetComponent<Transform>();
}

void EnemyShooter::Update(float deltaTime)
{
	Shoot(deltaTime);
}

void EnemyShooter::Shoot(float deltaTime)
{
	if (m_timer >= 50.f)
	{
		//shoot towards the player 
		Vector2 spawn_pos = m_shooter_transform->position - m_shooter_transform->forward * m_spawn_offset;
		bullet_pool.Spawn(spawn_pos, m_shooter_transform->forward * (-1.f), m_shooter_transform->rotation_angle);
		m_timer = 0.f;
	}

	m_timer += deltaTime / 100.f;
}

void EnemyShooter::SetBulletPool()
{
	bullet_pool.SetUp();
}
