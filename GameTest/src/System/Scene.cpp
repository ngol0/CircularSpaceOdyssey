#include "stdafx.h"
#include "Scene.h"
#include "LevelManager.h"
#include "AudioManager.h"
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
#include "Global/WaypointGenerator.h"
#include "Global/PowerUpType.h"

auto& collision_manager = CollisionManager::GetInstance();
auto& object_manager = GameObjectManager::GetInstance();
auto& window_manager = WindowManager::GetInstance();
auto& level_manager = LevelManager::GetInstance();
auto& audio_manager = AudioManager::GetInstance();

Scene::Scene() : m_score(0), m_player(nullptr)
{
	m_circle_center = Vector2{ 500.f, 400.f };
	m_circle_radius = 300.f;
	m_circle_steps = 30;
}

//init game objects
void Scene::Init()
{
	//planet
	m_planet = GameObjectFactory::CreateCombatPlanet(m_circle_center, m_circle_radius, m_circle_steps);

	//player
	m_player = GameObjectFactory::CreatePlayer(m_circle_center, m_circle_radius, 0.5f);
	m_player->GetComponent<BoxCollider>().collision_enter.Register(this, &Scene::OnPlayerCollisionEnter);
	m_player->GetComponent<Health>().on_die.Register(this, &Scene::OnGameOver);

	//particles
	m_explosion_particle_pool.Init();

	//powerups
	WaypointGenerator::InitWaypoints(m_circle_radius, m_circle_center, m_circle_steps, m_powerup_positions);
	m_health_powerup_pool.Init(PowerUpType::Health);

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
	if (other.tag == "health_power")
	{
		if (m_player->GetComponent<Health>().health_amount < GameGlobal::MAX_PLAYER_HEALTH)
		{
			m_player->GetComponent<Health>().health_amount += 2;
		}
		other.object->Deactivate();

		audio_manager.PlaySoundEffect(SoundID::HEALTH_POWER, false);
	}
	if (other.tag == "enemy")
	{
		m_player->GetComponent<Health>().TakeDamage(5);
		m_player->GetComponent<HitEffect>().Play();
		ExplosionParticleEmitter::Emit(m_explosion_particle_pool, other.object->GetComponent<Transform>().position);
		other.object->Deactivate();

		audio_manager.PlaySoundEffect(SoundID::PLAYER_DAMAGED, false);
	}
	if (other.tag == "enemy_bullet")
	{
		m_player->GetComponent<Health>().TakeDamage(1);
		m_player->GetComponent<HitEffect>().Play();
		other.object->Deactivate();

		audio_manager.PlaySoundEffect(SoundID::PLAYER_DAMAGED, false);
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
	m_health_powerup_pool.SetUp();

	SetUp(); //set up player pos & stats
	level_manager.Restart();

	//reset waypoints
	for (auto& wp : m_powerup_positions)
	{
		wp.is_available = true;
	}
}

//enemy die -- if score % 10 = 0, spawn a health power up; also check if win
void Scene::OnEnemyDie(const Vector2& pos)
{
	m_score++;

	//particle effect
	ExplosionParticleEmitter::Emit(m_explosion_particle_pool, pos);

	//health pickup every 10 points
	if (m_score % 10 == 0)
	{
		m_health_powerup_pool.Spawn(*WaypointGenerator::GetRandomlyAvailableWaypoint(m_powerup_positions));
	}

	//win condition
	if (m_score >= GameGlobal::MAX_SCORE)
	{
		window_manager.SetWindow(WindowState::win);
	}

	audio_manager.PlaySoundEffect(SoundID::ENEMY_EXPLODE, false);
}

//player die -- lose
void Scene::OnGameOver(const Vector2& pos)
{
	//particle effect
	ExplosionParticleEmitter::Emit(m_explosion_particle_pool, pos);

	//ui
	window_manager.SetWindow(WindowState::lose);

	//sound
	audio_manager.PlaySoundEffect(SoundID::PLAYER_EXPLODE, false);
}



