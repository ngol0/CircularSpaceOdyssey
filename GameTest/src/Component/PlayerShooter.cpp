#include "stdafx.h"
#include "PlayerShooter.h"
#include "Component/Transform.h"

PlayerShooter::PlayerShooter(float offset) : m_timer(0.f), m_spawn_offset(offset), m_shooter_transform(nullptr)
{
	bullet_pool.Init();
}

void PlayerShooter::Init()
{
	m_shooter_transform = &Component::object->GetComponent<Transform>();
}

void PlayerShooter::Update(float deltaTime)
{
	Shoot(deltaTime);
}

void PlayerShooter::Shoot(float deltaTime)
{
	if (App::IsKeyPressed(VK_RBUTTON) && m_timer >= 2.f)
	{
		Vector2 spawn_pos = m_shooter_transform->position + m_shooter_transform->forward * m_spawn_offset;
		bullet_pool.Spawn(spawn_pos, m_shooter_transform->forward, m_shooter_transform->rotation_angle);
		m_timer = 0.f;
	}

	m_timer += deltaTime / 100.f;
}

void PlayerShooter::SetBulletPool()
{
	bullet_pool.SetUp();
}