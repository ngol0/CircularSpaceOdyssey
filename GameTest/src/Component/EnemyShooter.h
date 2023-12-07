#pragma once
#include "GameObject/BulletPool.h"

class EnemyShooter : public Component
{
public:
	BulletPool bullet_pool{ 0.0f, 0.74, .78f, .15f, "enemy_bullet"};

	EnemyShooter(float offset);

	void Init() override;
	void Update(float deltaTime) override;
	void Render() override {};

	void Shoot(float deltaTime);
	void SetBulletPool();

private:
	float m_timer;
	float m_spawn_offset;
	Transform* m_shooter_transform;
};