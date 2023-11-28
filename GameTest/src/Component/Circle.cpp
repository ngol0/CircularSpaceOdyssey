#include "stdafx.h"
#include "Circle.h"
#include "Math/Vector2.h"

Circle::Circle() : m_xPos(0.f), m_yPos(0.f), m_radius(0.f), m_vertices_number(0), m_vertices{ Vector2() }
{

}

Circle::Circle(Vector2 center_position, float radius) : m_xPos(center_position.x), m_yPos(center_position.y), m_radius(radius)
{

}

void Circle::Init()
{
	for (int i = 0; i <= steps; i++)
	{
		float theta = 2.f * PI * i/steps;
		float newX = m_radius * (float)cos(theta) + m_xPos;
		float newY = m_radius * (float)sin(theta) + m_yPos;

		m_vertices.push_back(Vector2(newX, newY));
	}

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
		App::DrawLine(m_xPos, m_yPos, sx, sy, .2f, .3f, .5f); //inner
	}
}