#pragma once
#include "Component.h"
#include "Component/EnemySpawner.h"
#include "GameObject/EnemyPool.h"

class EnemySplit : public Component
{
public:
	EnemySplit(int child_number);
	void Init();
	void Split();

private:
	int m_child_number;
};
