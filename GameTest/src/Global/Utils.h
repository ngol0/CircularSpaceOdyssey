/* includes global methods to create dot/rectangle 
and generate circle vertices/random pos on screen/random int and float
*/
#pragma once
#include "Math/Vector2.h"

namespace Utils
{
	void GenerateCircleVertices(float radius, const Vector2& center, int steps, std::vector<Vector2>& out_vector);
	void DrawDot(const Vector2& position, float r, float g, float b);
	void DrawRectangle(const Vector2& position, float r, float g, float b, const Vector2& size);

	//random generator
	int RandomInt(int min, int max);
	float RandomFloat(float min, float max);

	float Distance(const Vector2& vector1, const Vector2& vector2);
};