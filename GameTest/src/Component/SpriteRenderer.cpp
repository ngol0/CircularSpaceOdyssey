#include "stdafx.h"
#include "SpriteRenderer.h"
#include "GameObject/GameObject.h"
#include "Component/Transform.h"

SpriteRenderer::SpriteRenderer(const char* spritename, int sprite_columns, int sprite_rows) : m_sprite(nullptr), transform(nullptr)
{
	name = "SpriteRenderer";

	m_sprite =  App::CreateSprite(spritename, sprite_columns, sprite_rows);
}

SpriteRenderer::~SpriteRenderer() { delete m_sprite; }

void SpriteRenderer::Init()
{
	transform = &Component::object->GetComponent<Transform>();
	m_sprite->SetPosition(transform->position.x, transform->position.y);
	m_sprite->SetScale(transform->scale);
}

void SpriteRenderer::Update(float deltaTime)
{
	m_sprite->Update(deltaTime);
	m_sprite->SetPosition(transform->position.x, transform->position.y);
	m_sprite->SetAngle(transform->rotation_angle);
}

void SpriteRenderer::Render()
{
	m_sprite->Draw();
}