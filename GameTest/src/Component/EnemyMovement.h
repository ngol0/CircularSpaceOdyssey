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
	void Update(float deltaTime) override;
	void Reset();

private:
	float m_speed;

	Waypoint* m_destination;
	Transform* m_transform;
};

enum class EnemyType
{
	ChaseType = 1,
	Type_2 = 5,
	Type_3 = 9,
	Type_4 = 13,
	ShootType = 17
};