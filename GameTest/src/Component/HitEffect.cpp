#include "stdafx.h"
#include "HitEffect.h"
#include "GameObject/GameObject.h"
#include "Transform.h"
#include "SpriteRenderer.h"

HitEffect::HitEffect(float offset) : m_scale_timer(0.f), m_offset(offset) {}

void HitEffect::Play()
{
	//scale up
	m_default_scale = Component::object->GetComponent<Transform>().scale;
	Component::object->GetComponent<SpriteRenderer>().SetScale(m_default_scale + m_offset);

	m_scale_timer = 0.3f;
}

void HitEffect::Update(float deltaTime)
{
	if (m_scale_timer == 0) return;
	m_scale_timer -= deltaTime / 100.f;
	if (m_scale_timer < 0)
	{
		Component::object->GetComponent<SpriteRenderer>().SetScale(m_default_scale);
		m_scale_timer = 0;
	}
}