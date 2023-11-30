#pragma once
#include "GameObject/BulletPool.h"


struct Shooter : public Component
{
	BulletPool bullet_pool;

	Shooter(float offset, Scene& scene);

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