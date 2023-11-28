#pragma once
#include "Component.h"

struct Health : public Component
{
	Health(int initial_amount);
	int amount;
	void TakeDamage(int damage_amount);

	void Init() {};
	void Update(float deltaTime) {};
};