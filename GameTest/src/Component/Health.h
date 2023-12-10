#pragma once
#include "Component.h"
#include "System/Event.h"

class Scene;

class Health : public Component
{
public:
	Health(int initial_amount);
	void TakeDamage(int damage_amount);

	void Init() {};
	void Update(float deltaTime) {};

	void ResetHealth();

	int amount;
	int initial_amount;

	Event<Scene> on_die;
};