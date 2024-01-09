#include "stdafx.h"
#include "EnemyRandomMovement.h"
//
#include "Math/Vector2.h"
#include "Global/Utils.h"
#include "GameObject/GameObject.h"
//
#include "Transform.h"
#include "EnemyMovement.h"

EnemyRandomMovement::EnemyRandomMovement() {}

void EnemyRandomMovement::Init()
{
	m_transform = &Component::object->GetComponent<Transform>();
	m_mover = &Component::object->GetComponent<EnemyMovement>();

	//init waypoints
	std::vector<Vector2> m_vertices;
	Utils::GenerateCircleVertices(m_distance_to_center, m_transform->position, m_vertices_number, m_vertices);

	for (auto& vertice : m_vertices)
	{
		m_waypoint_list.push_back(Waypoint{ vertice, true });
	}
}

Waypoint* EnemyRandomMovement::GetRandomWaypoint()
{
	int random_index = Utils::RandomInt(0, m_vertices_number);

	if (m_waypoint_list[random_index].is_available)
	{
		return &m_waypoint_list[random_index];
	}
	else
	{
		GetRandomWaypoint();
	}
}

void EnemyRandomMovement::GetNextDestination()
{
	//get waypoint
	Waypoint* next_destination = GetRandomWaypoint();

	//move the enemy
	m_mover->MoveTo(*next_destination);
}

void EnemyRandomMovement::Update(float deltaTime)
{

}