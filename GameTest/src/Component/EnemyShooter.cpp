#include "stdafx.h"
#include "EnemyShooter.h"
#include "Transform.h"
#include "MovementInput.h"
#include "Global/Utils.h"
#include "System/AudioManager.h"

EnemyShooter::EnemyShooter(float offset) : m_timer(0.f), m_spawn_offset(offset), m_shoot_time(0.f), m_shooter_transform(nullptr), m_target_position(nullptr)
{
	bullet_pool.Init();
}

void EnemyShooter::Init()
{
	m_shooter_transform = &Component::object->GetComponent<Transform>();
	m_shoot_time = Utils::RandomFloat(20.f, 80.f);
}

void EnemyShooter::Update(float deltaTime)
{
	Shoot(deltaTime);
}

void EnemyShooter::Shoot(float deltaTime)
{
	if (m_timer >= m_shoot_time)
	{
		//spawn pos for bullet
		Vector2 spawn_pos = m_shooter_transform->position - m_shooter_transform->forward * m_spawn_offset;

		//if target is moving - predict it's next pos
		if (m_target_input->IsMoving())
		{
			//calculate future position
			float angle_to_shoot = PredictTargetNextAngle();

			//shoot towards the predicted pos
			Vector2 shoot_pos;
			shoot_pos.x = m_center->x + cos(angle_to_shoot) * m_radius;
			shoot_pos.y = m_center->y + sin(angle_to_shoot) * m_radius;

			Vector2 shoot_direction = (shoot_pos - m_shooter_transform->position).normalize();

			bullet_pool.Spawn(spawn_pos, shoot_direction, m_shooter_transform->rotation_angle);
		}
		//if not, shoot towards target
		else
		{
			Vector2 shoot_direction = (*m_target_position - m_shooter_transform->position).normalize();
			bullet_pool.Spawn(spawn_pos, shoot_direction, m_shooter_transform->rotation_angle);
		}

		m_timer = 0.f;

		//sound
		AudioManager::GetInstance().PlaySoundEffect(SoundID::ENEMY_SHOOT, false);
	}

	m_timer += deltaTime / 100.f;
}

float EnemyShooter::PredictTargetNextAngle()
{
	//calculate the time for bullet to hit the target
	float distance_to_target = Utils::Distance(*m_target_position, m_shooter_transform->position);
	float delta_t = distance_to_target / m_bullet_speed;

	//predicting the amount of distance player will move in delta_t seconds
	float angular_displacement = m_target_input->GetAngularVelocity() * delta_t;

	//setting direction for future position
	if (m_target_input->IsClockWise()) angular_displacement = -angular_displacement;

	//calculate future angle to shoot at based on the amount of distance predicted
	return (m_target_input->GetAngle() + angular_displacement);
}

void EnemyShooter::SetBulletPool()
{
	bullet_pool.SetUp();
}

void EnemyShooter::SetTarget(const Object::Ref target, const Vector2& planet_pos)
{
	m_target_input = &target->GetComponent<MovementInput>();
	m_radius = m_target_input->GetDistanceToCenter();
	m_center = &planet_pos;
	m_target_position = &target->GetComponent<Transform>().position;
}
