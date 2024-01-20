#include "stdafx.h"
#include "EnemyPool.h"
#include "Component/EnemyMovement.h"
#include "Component/EnemyRandomMovement.h"
#include "Component/Transform.h"
#include "Component/BoxCollider.h"
//
#include "GameObjectFactory.h"
#include "System/Scene.h"
#include "Component/EnemyShooter.h"

EnemyPool::EnemyPool() {}

void EnemyPool::Init(Transform& transform, EnemyType enemy_type, Scene& scene)
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		enemies[i] = GameObjectFactory::CreateEnemy(transform, enemy_type);
		enemies[i]->Deactivate();
		enemies[i]->GetComponent<BoxCollider>().collisions_enter.Register(&scene, &Scene::OnEnemyCollisionEnter);
		enemies[i]->GetComponent<Health>().on_die.Register(&scene, &Scene::OnEnemyDie);

		if (enemies[i]->HasComponent<EnemyShooter>())
		{
			enemies[i]->GetComponent<EnemyShooter>().SetTarget(scene.GetPlayerPosition());
		}	
	}
}

//if spawn without pre-stated destination, the enemies move to random positions among the inner vertices
Object::Ref EnemyPool::Spawn(const Vector2& spawn_pos)
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		if (!enemies[i]->IsAlive())
		{
			enemies[i]->SetPosition(spawn_pos);
			enemies[i]->GetComponent<EnemyRandomMovement>().GetNextDestination();
			enemies[i]->Activate();

			return enemies[i];
		}
	}
}

//enemies move to outer vertices
Object::Ref EnemyPool::Spawn(const Vector2& spawn_pos, Waypoint& destination)
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		if (!enemies[i]->IsAlive())
		{
			enemies[i]->SetPosition(spawn_pos);
			enemies[i]->GetComponent<EnemyMovement>().MoveTo(destination);
			enemies[i]->Activate();

			return enemies[i];
		}
	}
}

//enemies move to specific position
Object::Ref EnemyPool::Spawn(const Vector2& spawn_pos, const Vector2& destination)
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		if (!enemies[i]->IsAlive())
		{
			enemies[i]->SetPosition(spawn_pos);
			enemies[i]->GetComponent<EnemyMovement>().MoveTo(destination);
			enemies[i]->Activate();

			return enemies[i];
		}
	}
}

void EnemyPool::SetUp()
{
	for (const auto& enemy : enemies)
	{
		enemy->Deactivate();

		if (enemy->HasComponent<EnemyShooter>())
		{
			enemy->GetComponent<EnemyShooter>().SetBulletPool();
		}
	}
}