#pragma once
#include "Component.h"
#include "System/Event.h"

class Scene;

struct Health : public Component
{
	Health(int initial_amount);
	void TakeDamage(int damage_amount);

	void Init() {};
	void Update(float deltaTime) {};

	void ResetHealth();

	int amount;
	int initial_amount;

	Event<Scene> on_die;
};