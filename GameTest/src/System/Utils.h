#pragma once
#include "Math/Vector2.h"
#include "Data.h"

namespace Utils
{
	void GenerateCircleVertices(float radius, const Vector2& center, int steps, std::vector<Vector2>& out_vector);
	void DrawDot(const Vector2& position, int r, int g, int b);
	void DrawRectangle(const Vector2& position, int r, int g, int b, const Vector2& size);

	Vector2& RandomPosition();
	int RandomInt(int min, int max);
	float RandomFloat(float min, float max);
	float RandomColor();

	EnemyType ConvertToEnemyType(const std::string& str);
};