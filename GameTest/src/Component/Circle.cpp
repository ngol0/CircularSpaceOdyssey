#include "stdafx.h"
#include "Circle.h"
#include "Math/Vector2.h"
#include "System/Utils.h"

Circle::Circle(const Vector2& center_position, float radius, int steps) : m_center(&center_position), m_radius(radius), m_vertices_number(0), m_steps(steps) {}

void Circle::Init()
{
	Utils::GenerateCircleVertices(m_radius, *m_center, 30, m_vertices);
	m_vertices_number = m_vertices.size();
}

void Circle::Render()
{
	for (int i = 0; i < m_vertices_number; i++)
	{
		int j = i;
		int k = (i+1) % m_vertices_number;
		float sx = m_vertices[j].x;
		float sy = m_vertices[j].y;
		float ex = m_vertices[k].x;
		float ey = m_vertices[k].y;
		App::DrawLine(sx, sy, ex, ey, .2f, 0.3f, 0.5f); //outer
		App::DrawLine(m_center->x, m_center->y, sx, sy, .2f, .3f, .5f); //inner
	}
}