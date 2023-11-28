#pragma once
#include "Component.h"

struct Transform;

struct SpriteRenderer : public Component
{
public:
	CSimpleSprite* m_sprite;
	float width() { return m_sprite->GetHeight() * m_sprite->GetScale(); };
	float height() { return m_sprite->GetWidth() * m_sprite->GetScale(); };

	SpriteRenderer(const char* spritename, int sprite_columns, int sprite_rows);
	~SpriteRenderer();

	void Init() override;
	void Update(float deltaTime) override;
	void Render() override;

	Transform* transform;
};