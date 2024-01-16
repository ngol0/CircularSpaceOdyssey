#include "stdafx.h"
#include "WaypointGenerator.h"
#include "Utils.h"

namespace WaypointGenerator
{
	Waypoint* GetRandomlyAvailableWaypoint(std::vector<Waypoint>& in_vector)
	{
		int random_index = Utils::RandomInt(0, in_vector.size() - 1);

		if (in_vector[random_index].is_available)
		{
			return &in_vector[random_index];
		}
		else
		{
			return GetNextAvailableWaypoint(in_vector);
		}
	}

	Waypoint* GetNextAvailableWaypoint(std::vector<Waypoint>& in_vector)
	{
		for (auto& waypoint : in_vector)
		{
			if (waypoint.is_available)
			{
				return &waypoint;
			}
		}
		return nullptr;
	}

	void InitWaypoints(float radius, const Vector2& center, int steps, std::vector<Waypoint>& out_vector)
	{
		std::vector<Vector2> m_vertices;
		Utils::GenerateCircleVertices(radius, center, steps, m_vertices);

		for (auto& vertice : m_vertices)
		{
			out_vector.push_back(Waypoint{ vertice, true });
		}
	}
}