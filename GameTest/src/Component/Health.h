#pragma once
#include "Component.h"
#include "Global/Event.h"

class Scene;
struct Vector2;

class Health : public Component
{
public:
	Health(int initial_amount);
	void TakeDamage(int damage_amount);

	void Init() {};
	void Update(float deltaTime) {};

	void ResetHealth();

	Event<Scene, const Vector2&> on_die;

	int health_amount;

private:
	int m_initial_amount;
};