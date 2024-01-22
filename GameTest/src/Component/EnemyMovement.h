/* Generic enemy movement component that sets a destination (waypoint or vector2)
* and moves the enemy there
*/
#pragma once
#include "Component.h"
#include "Math/Vector2.h"
#include "Global/Event.h"

class Transform;

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

	Waypoint* m_waypoint_destination;
	Transform* m_transform;
	const Vector2* m_pos_destination;
};