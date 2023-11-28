#include "stdafx.h"
#include "MovementInput.h"
#include "GameObject/GameObject.h"
#include "Math/Vector2.h"
#include "SpriteRenderer.h"

MovementInput::MovementInput() : m_speed(0.f), transform(nullptr), sprite(nullptr), m_center(Vector2{ 0.f }), m_distance(0.f), m_rotation_angle(0.f) {}

void MovementInput::Init()
{
	transform = &Component::object->GetComponent<Transform>();
	sprite = &Component::object->GetComponent<SpriteRenderer>();

	m_speed = 0.1f;
}

void MovementInput::SetMovementValue(const Vector2& center, float distance)
{
	m_center = center;
	m_distance = distance;
}

void MovementInput::Update(float deltaTime)
{
	if (App::GetController().GetLeftThumbStickX() > 0.5f)
	{
		//m_sprite->SetAnimation(ANIM_RIGHT);
		//transform->position.x += m_speed * deltaTime;

		m_degree += m_speed * deltaTime;

	}
	if (App::GetController().GetLeftThumbStickX() < -0.5f)
	{
		//m_sprite->SetAnimation(ANIM_LEFT);
		//transform->position.x -= m_speed * deltaTime;

		m_degree -= m_speed * deltaTime;
	}

	//if (App::GetController().GetLeftThumbStickY() > 0.5f)
	//{
	//	//m_sprite->SetAnimation(ANIM_BACKWARDS);
	//	transform->position.y -= m_speed * deltaTime;
	//}
	//if (App::GetController().GetLeftThumbStickY() < -0.5f)
	//{
	//	//m_sprite->SetAnimation(ANIM_FORWARDS);
	//	transform->position.y += m_speed * deltaTime;
	//}

	float radian = m_degree * (PI / 180);

	transform->position.x = m_center.x + cos(radian) * m_distance;
	transform->position.y = m_center.y + sin(radian) * m_distance;

	//update rotation
	Vector2 direction_to_center = (m_center - transform->position).normalize();
	m_rotation_angle = atan2(-direction_to_center.x, direction_to_center.y);

	Component::object->SetRotationAngle(m_rotation_angle);
	Component::object->SetForwardVector(direction_to_center);
}

void MovementInput::Restart()
{
	m_degree = 270.f;
}