#include "stdafx.h"
//
#include "Particle.h"
#include "Transform.h"
//
#include "GameObject/GameObject.h"

Particle::Particle(int lifespan) : m_frame_left(lifespan), m_initial_frame(lifespan), m_speed(0.f) {}

void Particle::Init()
{
	m_speed = 0.05f;
	m_transform = &Component::object->GetComponent<Transform>();
}

void Particle::Update(float deltaTime)
{
	m_frame_left--;
	m_transform->position = m_transform->position + m_move_direction * m_speed * deltaTime;

	if (m_frame_left <= 0)
	{
		Component::object->Deactivate();
	}
}

void Particle::SetDirection(float angle)
{
	//change to radian
	float radian = angle * PI / 180.f;

	//calculate x and y of direction vector
	m_move_direction.x = cos(radian);
	m_move_direction.y = sin(radian);
}

void Particle::ResetLife()
{
	m_frame_left = m_initial_frame;
}