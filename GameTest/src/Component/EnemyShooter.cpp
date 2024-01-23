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
			float angle_to_shoot = PredictTargetNextPosition();

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

float EnemyShooter::PredictTargetNextPosition()
{
	//getting player's angle & direction
	m_is_target_clockwise = m_target_input->IsClockWise();
	m_target_angle = m_target_input->GetAngle();
	m_target_angular_speed = m_target_input->GetAngularVelocity();

	//calculate delta t and angular displacement
	m_distance_to_target = Utils::Distance(*m_target_position, m_shooter_transform->position);
	float delta_t = m_distance_to_target / 0.3f;

	//predicting the amount of distance player will move in delta_t seconds
	float angular_displacement = m_target_angular_speed * delta_t;

	if (m_is_target_clockwise) angular_displacement = -angular_displacement;

	//calculate future angle to shoot at
	return (m_target_angle + angular_displacement);
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
