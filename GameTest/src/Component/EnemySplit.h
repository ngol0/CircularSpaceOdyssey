#pragma once
#include "Component.h"

class EnemySplit : public Component
{
public:
	EnemySplit(int child_number);
	void Split();

private:
	int m_child_number;
	float m_offset;
};
