#pragma once
#include "GameObject/BulletPool.h"


struct PlayerShooter : public Component
{
	BulletPool bullet_pool{1.f, 0.5, .2f, .2f, "player_bullet"};

	PlayerShooter(float offset);

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