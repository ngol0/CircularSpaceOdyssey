#pragma once
#include "Math/Vector2.h"
#include "Component.h"

class Circle : public Component
{
private:
	Vector2 m_center;
	float m_radius;
	std::size_t m_vertices_number;
	std::vector<Vector2> m_vertices;

public:
	Circle();
	Circle(const Vector2& center_position, float radius);

	void Init() override;
	void Render() override;
};