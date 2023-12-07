#pragma once
#include "Component.h"

struct Transform;

struct SpriteRenderer : public Component
{
	float width() { return m_sprite->GetHeight() * m_sprite->GetScale(); };
	float height() { return m_sprite->GetWidth() * m_sprite->GetScale(); };

	SpriteRenderer(const char* spritename, int sprite_columns, int sprite_rows);
	~SpriteRenderer();

	void Init() override;
	void Update(float deltaTime) override;
	void Render() override;

	void CreateAnimation(unsigned int id, float speed, const std::vector<int>& frames);
	void SetAnimation(int id);
	void SetFrame(unsigned int id);
	void SetColor(float r, float g, float b);

private:
	CSimpleSprite* m_sprite;
	Transform* transform;
};