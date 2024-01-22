/* Toggle defense mode for enemy by switching color and on defense boolean */
#pragma once
#include "Component.h"

class SpriteRenderer;

class EnemyDefense : public Component
{
public:
	EnemyDefense();

	void Init() override;
	void Update(float deltaTime) override;
	void SetMode();
	void CheckDefense();

private:
	float m_timer;
	bool m_on_defense;

	SpriteRenderer* m_sprite_renderer;
};

