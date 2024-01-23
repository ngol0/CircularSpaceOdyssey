#include "stdafx.h"
#include "MovementInput.h"
#include "GameObject/GameObject.h"
#include "Math/Vector2.h"

MovementInput::MovementInput(const Vector2& center, float distance) : m_speed(0.f), transform(nullptr), m_degree(0.f), m_center(&center), m_distance(distance), m_rotation_angle(0.f) {}

void MovementInput::Init()
{
	transform = &Component::object->GetComponent<Transform>();
	m_speed = 0.05f;
}

void MovementInput::SetUp()
{
	m_degree = (atan2(transform->position.y, transform->position.x) * 180.f)/PI;
	UpdateTransform();
}

void MovementInput::Update(float deltaTime)
{
	float prev_degree = m_degree;

	if (!App::GetController().GetLeftThumbStickX())
	{
		m_is_moving = false;
		return;
	}
	//counter-clockwise
	if (App::GetController().GetLeftThumbStickX() > 0.5f)
	{
		m_degree += m_speed * deltaTime;
		m_is_clockwise = false;
	}
	//clockwise
	if (App::GetController().GetLeftThumbStickX() < -0.5f)
	{
		m_degree -= m_speed * deltaTime;
		m_is_clockwise = true;
	}

	float delta_angle = abs(m_degree - prev_degree);
	float delta_radian = delta_angle * (PI / 180.f);

	// Calculate angular speed (radians per second)
	m_angular_speed = delta_radian / deltaTime;

	UpdateTransform();
	m_is_moving = true;
}

void MovementInput::UpdateTransform()
{
	//update position
	float radian = m_degree * (PI / 180.f);

	transform->position.x = m_center->x + cos(radian) * m_distance;
	transform->position.y = m_center->y + sin(radian) * m_distance;

	//update rotation
	Vector2 direction_to_center = (*m_center - transform->position).normalize();
	m_rotation_angle = atan2(-direction_to_center.x, direction_to_center.y);

	Component::object->SetRotationAngle(m_rotation_angle);
	Component::object->SetForwardVector(direction_to_center);
}