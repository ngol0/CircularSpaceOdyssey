/* Set moving direction for particles using direction of radian angle of a unit circle
* Moves the particle for an amount of frame and then deactivate it
*/
#pragma once
#include "Component.h"
#include "Math/Vector2.h"

class Transform;

class Particle : public Component
{
public:
	Particle(int lifepsan);
	void Init() override;
	void Update(float deltaTime);
	void SetDirection(float angle);
	void ResetLife();

private:
	int m_frame_left;
	int m_initial_frame;

	float m_speed;
	Vector2 m_move_direction;

	Transform* m_transform{ nullptr };
};
