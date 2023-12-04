#include "stdafx.h"
//--managers
#include "GameObjectManager.h"
#include "GameObjectFactory.h"
//--components
#include "Component/BoxCollider.h"
#include "Component/Health.h"
#include "Component/SpriteRenderer.h"
#include "Component/MovementInput.h"
#include "Component/Shooter.h"
#include "Component/BulletMovement.h"
#include "Component/Circle.h"
#include "Component/EnemyMovement.h"
#include "Component/EnemySpawner.h"

namespace GameObjectFactory
{
	Object::Ref CreatePlayer(const Vector2& center, float distance, float scale)
	{
		Object::Ref player = GameObjectManager::GetInstance().AddToManager();
		player->SetScale(scale);

		//---components
		//sprite
		auto& player_sprite = player->AddComponent<SpriteRenderer>(".\\Data\\Sprite\\ship.png", 1, 1);
		//collider
		Vector2 collider_size{ player_sprite.width() * 0.9f, player_sprite.height() * 0.6f };
		auto& player_collider = player->AddComponent<BoxCollider>("player", collider_size);
		//movement input, health & shooting input
		player->AddComponent<MovementInput>(center, distance);
		player->AddComponent<Health>(100);
		player->AddComponent<Shooter>(50.f);

		return player;
	}

	Object::Ref CreateCoin(Transform& transform)
	{
		Object::Ref coin = GameObjectManager::GetInstance().AddToManager(transform);
		//sprite
		auto& coin_spike = coin->AddComponent<SpriteRenderer>(".\\Data\\Sprite\\coin.bmp", 8, 1);
		//collider
		Vector2 collider_size{ coin_spike.width(), coin_spike.height() };
		coin->AddComponent<BoxCollider>("coin", collider_size);

		return coin;
	}

	Object::Ref CreateEnemy(Transform& transform)
	{
		//auto& spike = scene.object_manager.AddToManager(transform);
		Object::Ref enemy = GameObjectManager::GetInstance().AddToManager(transform);
		//sprite
		SpriteRenderer& enemy_sprite = enemy->AddComponent<SpriteRenderer>(".\\Data\\Sprite\\enemies.png", 4, 5);
		enemy_sprite.m_sprite->SetFrame(17); 
		//collider
		Vector2 collider_size{ enemy_sprite.width(), enemy_sprite.height() };
		auto& enemy_collision = enemy->AddComponent<BoxCollider>("enemy", collider_size);
		//health
		enemy->AddComponent<Health>(100);
		//movement
		enemy->AddComponent<EnemyMovement>();

		return enemy;
	}

	Object::Ref CreateBullet()
	{
		Object::Ref bullet = GameObjectManager::GetInstance().AddToManager();
		bullet->GetComponent<Transform>().scale = .5f;
		//sprite
		auto& bullet_sprite = bullet->AddComponent<SpriteRenderer>(".\\Data\\Sprite\\bullet.png", 1, 1);
		//collider
		Vector2 collider_size{ bullet_sprite.width(), bullet_sprite.height() };
		bullet->AddComponent<BoxCollider>("bullet", collider_size);
		//bullet auto movement
		bullet->AddComponent<BulletMovement>();

		return bullet;
	}

	Object::Ref CreateCombatPlanet(const Vector2& center_position, float radius)
	{
		Transform circle_transfrom{ center_position, radius };
		Object::Ref circle = GameObjectManager::GetInstance().AddToManager(circle_transfrom);
		//shape
		circle->AddComponent<Circle>(center_position, radius);
		//enemy spawner
		circle->AddComponent<EnemySpawner>();

		return circle;
	}
}
