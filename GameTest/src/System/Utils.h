#pragma once
#include "Math/Vector2.h"

#define PI 3.14159

namespace Utils
{
	void GenerateCircleVertices(float radius, const Vector2& center, int steps, std::vector<Vector2>& out_vector);
	void DrawDot(const Vector2& position, int r, int g, int b);
	void GenerateRandomPositions(int max_pos, std::vector<Vector2>& output);

	int RandomInt(int min, int max);
	float RandomFloat(float min, float max);
};