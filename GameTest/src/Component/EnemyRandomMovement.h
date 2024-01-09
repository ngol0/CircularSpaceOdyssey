#pragma once
#include "Component.h"

class Waypoint;
class Transform;
class EnemyMovement;

class EnemyRandomMovement : public Component
{
public:
	EnemyRandomMovement();

	void Init() override;
	void Update(float deltaTime) override;
	void GetNextDestination();
	Waypoint* GetRandomWaypoint();

private:
	std::vector<Waypoint> m_waypoint_list;
	
	float m_distance_to_center = 80.f;
	int m_vertices_number = 20;

	Transform* m_transform{ nullptr };
	EnemyMovement* m_mover{ nullptr };
};