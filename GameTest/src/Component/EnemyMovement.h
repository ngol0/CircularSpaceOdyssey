#pragma once
#include "Component.h"
#include "Math/Vector2.h"

struct Transform;
struct Waypoint;

class EnemyMovement : public Component
{
public:
	EnemyMovement();
	~EnemyMovement() {}

	void Init();
	void MoveTo(Waypoint& pos);
	void Update(float deltaTime) override;
	void Reset();

private:
	float m_speed;

	Waypoint* m_destination;
	Transform* m_transform;
};