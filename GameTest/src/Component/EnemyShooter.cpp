#include "stdafx.h"
#include "EnemyShooter.h"
#include "Component/Transform.h"
#include "Global/Utils.h"

EnemyShooter::EnemyShooter(float offset) : m_timer(0.f), m_spawn_offset(offset), m_shooter_transform(nullptr), m_target_transform(nullptr)
{
	bullet_pool.Init();
}

void EnemyShooter::Init()
{
	m_shooter_transform = &Component::object->GetComponent<Transform>();
	m_shoot_time = Utils::RandomFloat(20.f, 100.f);
}

void EnemyShooter::Update(float deltaTime)
{
	Shoot(deltaTime);
}

void EnemyShooter::Shoot(float deltaTime)
{
	if (m_timer >= m_shoot_time)
	{
		//shoot towards the player 
		Vector2 spawn_pos = m_shooter_transform->position - m_shooter_transform->forward * m_spawn_offset;
		Vector2 shoot_direction = (*m_target_transform - m_shooter_transform->position).normalize();
		bullet_pool.Spawn(spawn_pos, shoot_direction, m_shooter_transform->rotation_angle);

		m_timer = 0.f;
	}

	m_timer += deltaTime / 100.f;
}

void EnemyShooter::SetBulletPool()
{
	bullet_pool.SetUp();
}

void EnemyShooter::SetTarget(const Vector2& target)
{
	m_target_transform = &target;
}
