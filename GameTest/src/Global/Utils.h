#pragma once
#include "Math/Vector2.h"
#include "EnemyType.h"

namespace Utils
{
	void GenerateCircleVertices(float radius, const Vector2& center, int steps, std::vector<Vector2>& out_vector);
	void DrawDot(const Vector2& position, float r, float g, float b);
	void DrawRectangle(const Vector2& position, float r, float g, float b, const Vector2& size);

	//random generator
	Vector2& RandomPosition();
	int RandomInt(int min, int max);
	float RandomFloat(float min, float max);
	float RandomColor();

	EnemyType ConvertToEnemyType(const std::string& str);

	//waypoint generator
	//void GenerateOuterWaypoints(float distance, const Vector2& center);
	//void GenerateInnerWaypoints(float distance, const Vector2& center);
};