#pragma once
#include "GameObject.h"
#include "Math/Vector2.h"

enum class PowerUpType;

class PowerUpPool
{
public:
	PowerUpPool();

	void Init(PowerUpType powerup_type);
	void Spawn(Waypoint& spawn_pos);
	void SetUp();

private:
	static const int POOL_SIZE = 7;
	Object::Ref power_ups[POOL_SIZE];
};