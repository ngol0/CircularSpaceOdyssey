#pragma once
#include "Math/Vector2.h"
#include "Component.h"

class Circle : public Component
{
private:
	const Vector2* m_center;
	float m_radius;
	int m_steps;

	std::size_t m_vertices_number;
	std::vector<Vector2> m_vertices;

public:
	Circle(const Vector2& center_position, float radius, int steps);

	void Init() override;
	void Render() override;
};