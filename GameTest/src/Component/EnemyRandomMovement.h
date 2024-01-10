#pragma once
#include "Component.h"
#include "Math/Vector2.h"

class Transform;
class EnemyMovement;

class EnemyRandomMovement : public Component
{
public:
	EnemyRandomMovement();

	void Init() override;
	void GetNextDestination();

private:
	Transform* m_transform{ nullptr };
	EnemyMovement* m_mover{ nullptr };
	std::vector<Waypoint> m_inner_waypoints;
};