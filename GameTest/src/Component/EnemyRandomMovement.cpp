#include "stdafx.h"
#include "EnemyRandomMovement.h"
#include "Global/WaypointGenerator.h"
#include "GameObject/GameObject.h"
//
#include "Transform.h"
#include "EnemyMovement.h"

EnemyRandomMovement::EnemyRandomMovement() {}

void EnemyRandomMovement::Init()
{
	m_transform = &Component::object->GetComponent<Transform>();
	m_mover = &Component::object->GetComponent<EnemyMovement>();

	WaypointGenerator::InitWaypoints(80.f, m_transform->position, 20, m_inner_waypoints);
}

void EnemyRandomMovement::GetNextDestination()
{
	//get waypoint
	Waypoint* next_destination = WaypointGenerator::GetRandomlyAvailableWaypoint(m_inner_waypoints);

	//move the enemy
	m_mover->MoveTo(*next_destination);
}