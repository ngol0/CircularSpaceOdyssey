#include "stdafx.h"
#include "EnemyPool.h"
#include "Component/EnemyMovement.h"
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
		enemies[i]->GetComponent<Health>().on_die.Register(&scene, &Scene::OnScore);

		if (enemies[i]->HasComponent<EnemyShooter>())
		{
			enemies[i]->GetComponent<EnemyShooter>().SetTarget(scene.GetPlayer());
		}	
	}
}

Object::Ref EnemyPool::Spawn(const Vector2& spawn_pos, Waypoint& destination, float rotation_angle)
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
	return nullptr;
}

void EnemyPool::SetUp()
{
	for (const auto& enemy : enemies)
	{
		enemy->Deactivate();
	}
}