/* Create bullet pool and spawn the bullets every shoot_time */
#pragma once
#include "GameObject/BulletPool.h"

class MovementInput;

class EnemyShooter : public Component
{
public:
	BulletPool bullet_pool{ 0.0f, 0.74f, .78f, .15f, 150, 0.3f, "enemy_bullet"};

	EnemyShooter(float offset);

	void Init() override;
	void Update(float deltaTime) override;
	void Render() override {};

	void SetBulletPool();
	void SetTarget(const Object::Ref target, const Vector2& planet_pos);

private:
	float m_timer;
	float m_spawn_offset;
	float m_shoot_time;
	Transform* m_shooter_transform;
	const Vector2* m_target_position;

	//var to predict player's future pos
	float m_target_angular_speed{0.f};
	float m_target_angle{0.f};
	bool m_is_target_clockwise{false};
	float m_radius{0.f};
	const Vector2* m_center{nullptr};
	MovementInput* m_target_input{nullptr};
	float m_distance_to_target{0.f};

	float PredictTargetNextPosition();
	void Shoot(float deltaTime);
};