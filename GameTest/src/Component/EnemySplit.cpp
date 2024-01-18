#include "stdafx.h"
#include "EnemySplit.h"
#include "Transform.h"
#include "System/Level/LevelManager.h"

EnemySplit::EnemySplit(int child_number) : m_child_number(child_number), m_offset(30.f) {}

void EnemySplit::Split()
{
	Vector2 spawn_pos = Component::object->GetComponent<Transform>().position;
	//spawn a number of enemy children at parent's position
	for (int i = 0; i < m_child_number; i++)
	{
		LevelManager::GetInstance().GetChildSpawner()->SpawnEnemyAtPos
		(
			spawn_pos + i * m_offset,
			LevelManager::GetInstance().GetPlayerPosition()
		);
	}
}