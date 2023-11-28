#pragma once
#include "Math/Vector2.h"
#include "Component.h"

#define PI 3.14159

class Circle : public Component
{
private:
	float m_xPos;
	float m_yPos;
	float m_radius;
	std::size_t m_vertices_number;
	std::vector<Vector2> m_vertices;

	const int steps = 20;

public:
	Circle();
	Circle(Vector2 center_position, float radius);
	void Init() override;
	void Render() override;
};