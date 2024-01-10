#include "stdafx.h"
#include "Scene.h"
#include "LevelManager.h"
//
#include "Component/MovementInput.h"
#include "Component/PlayerShooter.h"
#include "Component/HitEffect.h"
#include "Component/EnemyDefense.h"
//
#include "System/CollisionManager.h"
#include "GameObject/GameObjectManager.h"
#include "GameObject/GameObjectFactory.h"
#include "UI/WindowManager.h"
#include "UI/LoseWindow.h"
#include "UI/VictoryWindow.h"
#include "Global/GameGlobal.h"
#include "Global/ParticleEmitter.h"

auto& collision_manager = CollisionManager::GetInstance();
auto& object_manager = GameObjectManager::GetInstance();
auto& window_manager = WindowManager::GetInstance();
auto& level_manager = LevelManager::GetInstance();

Scene::Scene() : m_score(0), m_player(nullptr)
{
	m_circle_center = Vector2{ 500.f, 400.f };
	m_circle_radius = 300.f;
}

//init game objects
void Scene::Init()
{
	//planet
	m_planet = GameObjectFactory::CreateCombatPlanet(m_circle_center, m_circle_radius);

	//player
	m_player = GameObjectFactory::CreatePlayer(m_circle_center, m_circle_radius, 0.5f);
	m_player->GetComponent<BoxCollider>().collision_enter.Register(this, &Scene::OnPlayerCollisionEnter);
	m_player->GetComponent<Health>().on_die.Register(this, &Scene::OnGameOver);

	//particles
	m_explosion_particle_pool.Init();

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
		m_player->GetComponent<Health>().TakeDamage(5);
		m_player->GetComponent<HitEffect>().Play();
		ExplosionParticleEmitter::Emit(m_explosion_particle_pool, other.object->GetComponent<Transform>().position);
		other.object->Deactivate();
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

		if (!enemy.object->HasComponent<EnemyDefense>())
		{
			enemy.object->GetComponent<Health>().TakeDamage(30);
			enemy.object->GetComponent<HitEffect>().Play();
		}
		else
		{
			enemy.object->GetComponent<EnemyDefense>().CheckDefense();
		}
	}
}

void Scene::Update(float deltaTime)
{
	level_manager.Update(deltaTime, GetPlayerPosition());
	collision_manager.Update(deltaTime);
	object_manager.Update(deltaTime);
}

void Scene::Render()
{
	object_manager.Render();
}

void Scene::Restart()
{
	//reactivate game objects
	object_manager.Reactivate();
	//deactivates pool objects
	m_player->GetComponent<PlayerShooter>().SetBulletPool();
	//reset particle pool
	m_explosion_particle_pool.SetUp();

	SetUp(); //set up player pos & stats
	level_manager.Restart();
}

//enemy die -- if score % 10 = 0, spawn a health power up; also check if win
void Scene::OnEnemyDie(const Vector2& pos)
{
	m_score++;

	//particle effect
	ExplosionParticleEmitter::Emit(m_explosion_particle_pool, pos);

	//health pickup
	

	//win condition
	if (m_score >= GameGlobal::MAX_SCORE)
	{
		WindowManager::GetInstance().SetWindow(WindowState::win);
	}
}

//player die -- lose
void Scene::OnGameOver(const Vector2& pos)
{
	//particle effect
	ExplosionParticleEmitter::Emit(m_explosion_particle_pool, pos);

	window_manager.SetWindow(WindowState::lose);
}



