#pragma once
#include "Component.h"

class EnemyRandomMovement : public Component
{
public:
	EnemyRandomMovement();

	void GenerateRandomDirection();
	void Update(float deltaTime) override;
};