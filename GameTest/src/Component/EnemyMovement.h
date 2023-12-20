#pragma once
#include "Component.h"
#include "Math/Vector2.h"

class Transform;
struct Waypoint;

class EnemyMovement : public Component
{
public:
	EnemyMovement(float speed);
	~EnemyMovement() {}

	void Init();
	void MoveTo(Waypoint& pos);
	void MoveTo(const Vector2& pos);
	void Update(float deltaTime) override;
	void Reset();

private:
	float m_speed;

	Waypoint* m_destination;
	Transform* m_transform;
	const Vector2* m_pos;
};