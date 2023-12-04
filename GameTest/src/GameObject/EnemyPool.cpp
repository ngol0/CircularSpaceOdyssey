#include "stdafx.h"
#include "EnemyPool.h"
#include "Component/EnemyMovement.h"
#include "Component/Transform.h"
#include "Component/BoxCollider.h"
//
#include "GameObjectFactory.h"
#include "System/Scene.h"

EnemyPool::EnemyPool() {}

void EnemyPool::Init(Transform& transform, Scene& scene)
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		enemies[i] = GameObjectFactory::CreateEnemy(transform);
		enemies[i]->Deactivate();
		enemies[i]->GetComponent<BoxCollider>().collisions_enter.Register(&scene, &Scene::OnEnemyCollisionEnter);
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