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

	void DrawDot(const Vector2& position, float r, float g, float b)
	{
		App::DrawLine(position.x, position.y, position.x + 1, position.y + 1, r, g, b);
	}

	void DrawRectangle(const Vector2& position, float r, float g, float b, const Vector2& size)
	{
		App::DrawLine(position.x, position.y, position.x + size.x, position.y, r, g, b);
		App::DrawLine(position.x, position.y, position.x, position.y + size.y, r, g, b);

		App::DrawLine(position.x, position.y + size.y, position.x + size.x, position.y + size.y, r, g, b);
		App::DrawLine(position.x + size.x, position.y, position.x + size.x, position.y + size.y, r, g, b);
	}

	Vector2& RandomPosition()
	{
		float x = Utils::RandomFloat(0.f, 1000.f);
		float y = Utils::RandomFloat(0.f, 1000.f);

		return Vector2{ x,y };
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

	//todo: implement this?
	float RandomColor()
	{
		return 0.f;
	}

	EnemyType ConvertToEnemyType(const std::string& str)
	{
		if (str == "Shoot") return EnemyType::ShootType;
		else if (str == "Chase") return EnemyType::ChaseType;
	}
}