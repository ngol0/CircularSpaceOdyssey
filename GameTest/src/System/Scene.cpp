#include "stdafx.h"
#include "Scene.h"
#include "Component/Transform.h"
#include "Component/MovementInput.h"

Scene::Scene() : m_score(0), m_player(nullptr)
{
	circle_center = Vector2{ 500.f, 400.f };
	circle_radius = 300.f;
}

//init game objects
void Scene::Init()
{
	//circle
	GameObject* circle = &GameObjectFactory::CreateCircle(circle_center, circle_radius, *this);

	//player
	m_player = &GameObjectFactory::CreatePlayer(0.5f, *this);
	m_player->GetComponent<MovementInput>().SetMovementValue(circle_center, circle_radius);

	//coin
	for (int i = 0; i < 5; i++)
	{
		Transform coin_transform = Transform{ Vector2{ 200.f + i * 100.f, 300.f }, 0.5f };
		GameObject* coin = &GameObjectFactory::CreateCoin(coin_transform, *this);
	}

	//spike
	for (int i = 0; i < 5; i++)
	{
		Transform spike_transform = Transform{ Vector2{ 500.f + i * 90.f, 500.f }, 0.3f };
		GameObject* spike = &GameObjectFactory::CreateEnemy(spike_transform, *this);
	}
}

void Scene::OnPlayerCollisionEnter(BoxCollider& other)
{
	std::cout << "Player is collided with " << other.tag << std::endl;

	if (other.tag == "coin")
	{
		m_score++;
		other.object->Deactivate();
	}
	else if (other.tag == "spike")
	{
		m_player->GetComponent<Health>().TakeDamage(1);
	}
}

void Scene::OnEnemyCollisionEnter(BoxCollider& enemy, BoxCollider& other)
{
	if (other.tag == "bullet")
	{
		std::cout << "Enemy is collided with bullet." << std::endl;
		other.object->Deactivate();
		enemy.object->GetComponent<Health>().TakeDamage(50);
	}
}

void Scene::Update(float deltaTime)
{
	object_manager.Update(deltaTime);
	collision_manager.Update(deltaTime);

	//restart
	if (App::IsKeyPressed('R'))
	{
		object_manager.Restart();
	}
}

void Scene::Render()
{
	object_manager.Render();
}

void Scene::Shutdown()
{
}



