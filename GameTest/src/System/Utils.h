#pragma once
#include "Math/Vector2.h"

#define PI 3.14159

namespace Utils
{
	void GenerateCircleVertices(float radius, const Vector2& center, int steps, std::vector<Vector2>& out_vector);
	int RandomInt(int min, int max);
	float RandomFloat(float min, float max);
};