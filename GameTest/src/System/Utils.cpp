#include "stdafx.h"
#include "Math/Vector2.h"
#include "Utils.h"

#include <limits>
#include <random>

namespace Utils
{
	void GenerateCircleVertices(float radius, const Vector2& center, int steps, std::vector<Vector2>& out_vector)
	{
		for (int i = 0; i <= steps; i++)
		{
			float theta = 2.f * PI * i / steps;
			float newX = radius * (float)cos(theta) + center.x;
			float newY = radius * (float)sin(theta) + center.y;

			out_vector.push_back(Vector2(newX, newY));
		}
	}

	int RandomInt(int min, int max)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(min, max);
		return dis(gen);
	}

	float RandomFloat(float min, float max)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> dis(min, max);
		return dis(gen);
	}
}