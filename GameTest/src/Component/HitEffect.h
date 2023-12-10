#pragma once
#include "Component.h"

class HitEffect : public Component
{
public:
	HitEffect(float offset);

	void Play();
	void Update(float deltaTime);

private:
	float m_scale_timer;
	float m_default_scale;
	float m_offset;
};