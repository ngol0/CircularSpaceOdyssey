#include "stdafx.h"
#include "EnemyDefense.h"
#include "SpriteRenderer.h"
#include "Health.h"
#include "HitEffect.h"
//
#include "GameObject/GameObject.h"

EnemyDefense::EnemyDefense() : m_timer(0.f), m_on_defense(false), m_sprite_renderer(nullptr)
{

}

void EnemyDefense::Init()
{
	m_sprite_renderer = &Component::object->GetComponent<SpriteRenderer>();
}

void EnemyDefense::Update(float deltaTime)
{
	m_timer += deltaTime / 100.f;

	if (m_timer > 30.f)
	{
		m_on_defense = !m_on_defense;
		SetMode();
		m_timer = 0.f;
	}
}

void EnemyDefense::SetMode()
{
	if (m_on_defense)
	{
		m_sprite_renderer->SetColor(1.f, 0.2f, 0.f);
	}
	else
	{
		m_sprite_renderer->SetColor(0.f, 1.f, 0.212f);
	}
}

void EnemyDefense::CheckDefense()
{
	if (m_on_defense) return;
	Component::object->GetComponent<Health>().TakeDamage(30);
	Component::object->GetComponent<HitEffect>().Play();
}