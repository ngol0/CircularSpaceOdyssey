/* Create bullet pool and spawn the bullets every shoot_time */
#pragma once
#include "GameObject/BulletPool.h"

class MovementInput;

class EnemyShooter : public Component
{
private:
	float m_timer;
	float m_spawn_offset;
	float m_shoot_time;

	//positions
	Transform* m_shooter_transform;
	const Vector2* m_target_position;

	//var to predict player's future pos
	MovementInput* m_target_input{ nullptr };
	float m_bullet_speed{ 0.3f };

	//circle
	float m_radius{ 0.f };
	const Vector2* m_center{ nullptr };

	float PredictTargetNextAngle();
	void Shoot(float deltaTime);

public:
	BulletPool bullet_pool{ 0.0f, 0.74f, .78f, .15f, 150, m_bullet_speed, "enemy_bullet"};

	EnemyShooter(float offset);

	void Init() override;
	void Update(float deltaTime) override;
	void Render() override {};

	void SetBulletPool();
	void SetTarget(const Object::Ref target, const Vector2& planet_pos);
};