/* Hit effect component for both player and enemy */
#pragma once
#include "Component.h"

class SpriteRenderer;

class HitEffect : public Component
{
public:
	HitEffect(float offset);

	void Init() override;
	void Play();
	void Update(float deltaTime);

private:
	float m_scale_timer;
	float m_default_scale;
	float m_offset;

	SpriteRenderer* m_sprite;
};