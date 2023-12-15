#include "stdafx.h"
//--managers
#include "GameObjectManager.h"
#include "GameObjectFactory.h"
//--components
#include "Component/BoxCollider.h"
#include "Component/Health.h"
#include "Component/SpriteRenderer.h"
#include "Component/MovementInput.h"
#include "Component/PlayerShooter.h"
#include "Component/BulletMovement.h"
#include "Component/Circle.h"
#include "Component/EnemyMovement.h"
#include "Component/EnemySpawner.h"
#include "Component/EnemyShooter.h"
#include "Component/HitEffect.h"

namespace GameObjectFactory
{
	Object::Ref CreatePlayer(const Vector2& center, float distance, float scale)
	{
		Object::Ref player = GameObjectManager::GetInstance().AddToManager();
		player->SetScale(scale);

		//---components
		//sprite
		auto& player_sprite = player->AddComponent<SpriteRenderer>(".\\Data\\Sprite\\player.png", 4, 1);
		//player_sprite.CreateAnimation(0, 0.05f, { 0,1,2,3 });
		//player_sprite.SetAnimation(0);
		//collider
		Vector2 collider_size{ player_sprite.width() * 0.9f, player_sprite.height() * 0.6f };
		auto& player_collider = player->AddComponent<BoxCollider>("player", collider_size);
		//movement input, health & shooting input
		player->AddComponent<MovementInput>(center, distance);
		player->AddComponent<Health>(100);
		player->AddComponent<PlayerShooter>(25.f);
		player->AddComponent<HitEffect>(0.1f);

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

	Object::Ref CreateEnemy(Transform& transform, EnemyType enemy_type)
	{
		//auto& spike = scene.object_manager.AddToManager(transform);
		Object::Ref enemy = GameObjectManager::GetInstance().AddToManager(transform);
		//sprite
		SpriteRenderer& enemy_sprite = enemy->AddComponent<SpriteRenderer>(".\\Data\\Sprite\\enemies.png", 4, 5);
		enemy_sprite.SetFrame((int)enemy_type);
		//collider
		Vector2 collider_size{ enemy_sprite.width(), enemy_sprite.height()/2 };
		auto& enemy_collision = enemy->AddComponent<BoxCollider>("enemy", collider_size);
		//hit effect, input the scale offset
		enemy->AddComponent<HitEffect>(0.2f);

		switch (enemy_type)
		{
		case EnemyType::ChaseType:
			//health
			enemy->AddComponent<Health>(100);
			//movement
			enemy->AddComponent<EnemyMovement>(0.02f);
			break;
		case EnemyType::ShootType:
			enemy->AddComponent<Health>(200);
			//shooter
			enemy->AddComponent<EnemyShooter>(20.f);
			//movement
			enemy->AddComponent<EnemyMovement>(0.2f);
			break;
		}
		return enemy;
	}

	Object::Ref CreateBullet(float r, float b, float g, float size, int lifespan, std::string tag)
	{
		Object::Ref bullet = GameObjectManager::GetInstance().AddToManager();
		bullet->GetComponent<Transform>().scale = size;
		//sprite
		auto& bullet_sprite = bullet->AddComponent<SpriteRenderer>(".\\Data\\Sprite\\bullet.png", 1, 1);
		bullet_sprite.SetColor(r,b,g);
		//collider
		Vector2 collider_size{ bullet_sprite.width(), bullet_sprite.height() };
		bullet->AddComponent<BoxCollider>(tag, collider_size);
		//bullet auto movement
		bullet->AddComponent<BulletMovement>(lifespan);

		return bullet;
	}

	Object::Ref CreateCombatPlanet(const Vector2& center_position, float radius)
	{
		Transform circle_transfrom{ center_position, radius };
		Object::Ref circle = GameObjectManager::GetInstance().AddToManager(circle_transfrom);
		//shape
		circle->AddComponent<Circle>(center_position, radius, 30);

		return circle;
	}

	Object::Ref CreateShootEnemySpawner(const Vector2& spawn_pos)
	{
		Transform transform{ spawn_pos, 0.f };
		Object::Ref spawner = GameObjectManager::GetInstance().AddToManager(transform);
		//enemy spawner
		spawner->AddComponent<EnemySpawner>();

		return spawner;
	}

	Object::Ref CreateChaseEnemySpawner(const Vector2& spawn_pos)
	{
		Transform transform{ spawn_pos, 0.f };
		Object::Ref spawner = GameObjectManager::GetInstance().AddToManager(transform);
		//enemy spawner
		spawner->AddComponent<EnemySpawner>();

		return spawner;
	}
}
