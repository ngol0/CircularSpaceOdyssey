#include "stdafx.h"
//--managers
#include "GameObjectManager.h"
#include "GameObjectFactory.h"
#include "System/CollisionManager.h"
#include "System/Scene.h"
//--components
#include "Component/BoxCollider.h"
#include "Component/Health.h"
#include "Component/SpriteRenderer.h"
#include "Component/MovementInput.h"
#include "Component/Shooter.h"
#include "Component/BulletMovement.h"
#include "Component/Circle.h"


Core::Ref GameObjectFactory::CreatePlayer(float scale, Scene& scene)
{
	auto player = scene.object_manager.AddToManager();
	player->SetScale(scale);

	//components
	//sprite
	auto& player_sprite = player->AddComponent<SpriteRenderer>(".\\Data\\Sprite\\ship.png", 1, 1);
	//collider
	Vector2 collider_size{ player_sprite.width() * 0.9f, player_sprite.height() * 0.6f };
	auto& player_collider = player->AddComponent<BoxCollider>("player", collider_size, scene.collision_manager);
	//movement input, health & shooting input
	player->AddComponent<MovementInput>();
	player->AddComponent<Health>(100);
	player->AddComponent<Shooter>(50.f, scene);

	//event register for collision
	player_collider.collision_enter.Register(&scene, &Scene::OnPlayerCollisionEnter);

	return player;
}

Core::Ref GameObjectFactory::CreateCoin(Transform& transform, Scene& scene)
{
	auto coin = scene.object_manager.AddToManager(transform);
	//sprite
	auto& coin_spike = coin->AddComponent<SpriteRenderer>(".\\Data\\Sprite\\coin.bmp", 8, 1);
	//collider
	Vector2 collider_size{ coin_spike.width(), coin_spike.height() };
	coin->AddComponent<BoxCollider>("coin", collider_size, scene.collision_manager);

	return coin;
}

Core::Ref GameObjectFactory::CreateEnemy(Transform& transform, Scene& scene)
{
	//auto& spike = scene.object_manager.AddToManager(transform);
	auto spike = scene.object_manager.AddToManager(transform);
	//sprite
	auto& spike_sprite = spike->AddComponent<SpriteRenderer>(".\\Data\\Sprite\\spike.png", 1, 1);
	//collider
	Vector2 collider_size{ spike_sprite.width(), spike_sprite.height() };
	auto& spike_collision = spike->AddComponent<BoxCollider>("spike", collider_size, scene.collision_manager);
	//health
	spike->AddComponent<Health>(100);

	spike_collision.collisions_enter.Register(&scene, &Scene::OnEnemyCollisionEnter);

	return spike;
}

Core::Ref GameObjectFactory::CreateBullet(Scene& scene)
{
	auto bullet = scene.object_manager.AddToManager();
	bullet->GetComponent<Transform>().scale = .5f;
	//sprite
	auto& bullet_sprite = bullet->AddComponent<SpriteRenderer>(".\\Data\\Sprite\\bullet.png", 1, 1);
	//collider
	Vector2 collider_size{ bullet_sprite.width(), bullet_sprite.height() };
	bullet->AddComponent<BoxCollider>("bullet", collider_size, scene.collision_manager);
	//bullet auto movement
	bullet->AddComponent<BulletMovement>();

	return bullet;
}

Core::Ref GameObjectFactory::CreateCircle(const Vector2& center_position, float radius, Scene& scene)
{
	Transform circle_transfrom{ center_position, radius };
	std::shared_ptr<GameObject> circle = scene.object_manager.AddToManager(circle_transfrom);
	//shape
	circle->AddComponent<Circle>(center_position, radius);

	return circle;
}