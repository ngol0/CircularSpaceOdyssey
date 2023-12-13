#include "stdafx.h"
#include "Scene.h"
#include "Component/Transform.h"
#include "Component/MovementInput.h"
#include "Component/PlayerShooter.h"
#include "Component/HitEffect.h"
#include "Component/EnemyMovement.h"
//
#include "GameObject/GameObjectManager.h"
#include "System/CollisionManager.h"

Scene::Scene() : m_score(0), m_player(nullptr)
{
	circle_center = Vector2{ 500.f, 400.f };
	circle_radius = 300.f;

	m_scene_state = SceneState::START;
}

//init game objects
void Scene::Init()
{
	//planet
	m_planet = GameObjectFactory::CreateCombatPlanet(circle_center, circle_radius);
	m_planet->GetComponent<EnemySpawner>().SetUp(m_shoot_enemy_pool);

	//enemy
	Transform enemy_transform = Transform{ circle_center, 1.2f };
	m_shoot_enemy_pool.Init(enemy_transform, EnemyType::ShootType, *this);

	//player
	m_player = GameObjectFactory::CreatePlayer(circle_center, circle_radius, 0.5f);
	m_player->GetComponent<BoxCollider>().collision_enter.Register(this, &Scene::OnPlayerCollisionEnter);

	//coin
	/*for (int i = 0; i < 5; i++)
	{
		Transform coin_transform = Transform{ Vector2{ 200.f + i * 150.f, 300.f }, 0.5f };
		Core::Ref coin = GameObjectFactory::CreateCoin(coin_transform, *this);
	}*/

	SetUp();
}

void Scene::SetUp()
{
	m_player->SetPosition(Vector2(0.f, -1.f)); //starting position
	m_player->GetComponent<MovementInput>().SetUp();
	m_player->GetComponent<Health>().ResetHealth();

	m_score = 0; 
}

void Scene::OnPlayerCollisionEnter(BoxCollider& other)
{
	if (other.tag == "coin")
	{
		//todo: special power

		other.object->Deactivate();
	}
	if (other.tag == "enemy")
	{
		m_player->GetComponent<Health>().TakeDamage(1);
	}
	if (other.tag == "enemy_bullet")
	{
		m_player->GetComponent<Health>().TakeDamage(1);
		m_player->GetComponent<HitEffect>().Play();
		other.object->Deactivate();
	}
}

void Scene::OnEnemyCollisionEnter(BoxCollider& enemy, BoxCollider& other)
{
	if (other.tag == "player_bullet")
	{
		other.object->Deactivate();
		enemy.object->GetComponent<Health>().TakeDamage(30);
		enemy.object->GetComponent<HitEffect>().Play();
	}
}

void Scene::OnScore()
{
	m_score++;
}

void Scene::Update(float deltaTime)
{
	//spawn enemy
	m_planet->GetComponent<EnemySpawner>().SpawnEnemy(0.f, deltaTime);

	GameObjectManager::GetInstance().Update(deltaTime);
	CollisionManager::GetInstance().Update(deltaTime);
}

void Scene::Render()
{
	GameObjectManager::GetInstance().Render();
}

void Scene::Restart()
{
	//reactivate game objects
	GameObjectManager::GetInstance().Reactivate();

	//deactivates pool objects
	m_player->GetComponent<PlayerShooter>().SetBulletPool();
	m_shoot_enemy_pool.SetUp();

	//reset waypoints and timer
	m_planet->GetComponent<EnemySpawner>().Reset();
	
	SetUp(); //set up player pos & stats
}

void Scene::HandleInput(float deltaTime)
{
	switch (m_scene_state)
	{
	case SceneState::START:
		if (App::IsKeyPressed(VK_SPACE)) //start
		{
			m_scene_state = SceneState::COMBAT;
		}
		break;

	case SceneState::COMBAT:
		if (App::IsKeyPressed('R')) //restart
		{
			Restart();
		}
		if (App::IsKeyPressed('P') && m_timer >= 2.f) //pause
		{
			m_scene_state = SceneState::PAUSED;
			m_timer = 0.f;
		}
		break;

	case SceneState::PAUSED:
		if (App::IsKeyPressed('R')) //restart
		{
			Restart();
		}
		if (App::IsKeyPressed('P') && m_timer >= 2.f) //play
		{
			m_scene_state = SceneState::COMBAT;
			m_timer = 0.f;
		}
		break;

	case SceneState::GAME_OVER:
		if (App::IsKeyPressed('R')) //restart
		{
			Restart();
		}
		break;
	}

	m_timer += deltaTime / 100.f;
}



