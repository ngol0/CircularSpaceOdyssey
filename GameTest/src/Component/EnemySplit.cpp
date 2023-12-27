#include "stdafx.h"
#include "EnemySplit.h"
#include "Transform.h"
//
#include "Global/EnemyType.h"
#include "System/LevelManager.h"
#include "GameObject/GameObjectFactory.h"

EnemySplit::EnemySplit(int child_number) : m_child_number(child_number)
{

}

void EnemySplit::Init()
{
	
}

void EnemySplit::Split()
{
	Vector2 spawn_pos = Component::object->GetComponent<Transform>().position;
	//spawn a number of enemy children at split position
	for (int i = 0; i < m_child_number; i++)
	{
		LevelManager::GetInstance().GetChildSpawner()->SpawnEnemyAtPos
		(
			spawn_pos,
			LevelManager::GetInstance().GetPlayerPos()
		);
	}
}