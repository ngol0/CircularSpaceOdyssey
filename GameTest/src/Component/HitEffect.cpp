#include "stdafx.h"
#include "HitEffect.h"
#include "GameObject/GameObject.h"
#include "Transform.h"
#include "SpriteRenderer.h"

HitEffect::HitEffect(float offset) : m_scale_timer(0.f), m_default_scale(0.f), m_offset(offset), m_sprite(nullptr) 
{

}

void HitEffect::Init()
{
	m_default_scale = Component::object->GetComponent<Transform>().scale;
	m_sprite = &Component::object->GetComponent<SpriteRenderer>();
}

void HitEffect::Play()
{
	//scale up
	m_sprite->SetScale(m_default_scale + m_offset);
	m_scale_timer = 0.8f;
}

void HitEffect::Update(float deltaTime)
{
	if (m_scale_timer != 0)
	{
		m_scale_timer -= deltaTime / 100.f;
	}

	if (m_scale_timer < 0)
	{
		m_sprite->SetScale(m_default_scale);
		m_scale_timer = 0;
	}
}