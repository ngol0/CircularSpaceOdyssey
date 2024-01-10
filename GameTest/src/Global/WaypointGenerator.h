#pragma once
#include "Math/Vector2.h"

namespace WaypointGenerator
{
	void InitWaypoints(float radius, const Vector2& center, int steps, std::vector<Waypoint>& out_vector);
	Waypoint* GetNextAvailableWaypoint(std::vector<Waypoint>& in_vector);
	Waypoint* GetRandomlyAvailableWaypoint(std::vector<Waypoint>& in_vector);
}