#include "stdafx.h"
#include "LevelManager.h"
#include "GameObject/GameObjectFactory.h"
#include "Global/EnemyType.h"
#include "Global/Utils.h"
#include "Global/WaypointGenerator.h"
//
#include <sstream>

LevelManager::LevelManager() {}

void LevelManager::SetLevel(int current_level)
{
	m_current_level = current_level;
	SetUpTimer();
}

void LevelManager::LoadFile(const char* filename)
{
	m_input.open(filename);
	if (!m_input.is_open())
	{
		//std::cerr << "Failed to open file." << std::endl;
		return;
	}
	ReadCommandInfo();
	m_input.close();
}

void LevelManager::ReadCommandInfo()
{
	m_commands.clear();
	std::string line;

	while (std::getline(m_input, line))
	{
		std::istringstream iss(line);
		std::string commandType;
		iss >> commandType;

		std::unique_ptr<Command> cmd = std::make_unique<Command>();
		if (commandType == "Spawn")
		{
			cmd->command = CommandType::SPAWN;
			iss >> cmd->timer >> cmd->id;
			
		}
		else if (commandType == "Wait") 
		{
			cmd->command = CommandType::WAIT;
		}

		m_commands.emplace_back(std::move(cmd));
	}
}

void LevelManager::Init(Scene& scene)
{
	SetUpEnemy(scene);
	SetUpTimer();
}

void LevelManager::SetUpEnemy(Scene& scene)
{
	m_scene = &scene;
	//enemy pools
	Transform starting_transform = Transform{ scene.GetPlanetPosition(), 1.2f };
	m_chase_pool.Init(starting_transform, EnemyType::SlowChaseType, scene);
	m_shoot_pool.Init(starting_transform, EnemyType::ShootType, scene);
	m_child_pool.Init(starting_transform, EnemyType::FastChaseType, scene);
	m_split_pool.Init(starting_transform, EnemyType::SplitType, scene);
	m_defense_pool.Init(starting_transform, EnemyType::TwoModeType, scene);

	//enemy spawner init
	//slow chase enemy
	m_chase_spawner_obj = GameObjectFactory::CreateEnemySpawner(scene.GetPlanetPosition());
	m_chase_spawner = &m_chase_spawner_obj->GetComponent<EnemySpawner>();
	m_chase_spawner->SetUp(m_chase_pool);

	//shoot enemy that stays at waypoint
	m_shoot_spawner_obj = GameObjectFactory::CreateEnemySpawner(scene.GetPlanetPosition());
	m_shoot_spawner = &m_shoot_spawner_obj->GetComponent<EnemySpawner>();
	m_shoot_spawner->SetUp(m_shoot_pool);

	//enemy that can splits into different ones if destroyed
	m_split_spawner_obj = GameObjectFactory::CreateEnemySpawner(scene.GetPlanetPosition());
	m_split_spawner = &m_split_spawner_obj->GetComponent<EnemySpawner>();
	m_split_spawner->SetUp(m_split_pool);

	//splitted enemy that follows player in fast speed
	m_child_spawner_obj = GameObjectFactory::CreateEnemySpawner(scene.GetPlanetPosition());
	m_child_spawner = &m_child_spawner_obj->GetComponent<EnemySpawner>();
	m_child_spawner->SetUp(m_child_pool);

	//two mode enemy that can be shot when green and immune to bullet when red
	m_defense_spawner_obj = GameObjectFactory::CreateEnemySpawner(scene.GetPlanetPosition());
	m_defense_spawner = &m_defense_spawner_obj->GetComponent<EnemySpawner>();
	m_defense_spawner->SetUp(m_defense_pool);

	//init waypoints
	WaypointGenerator::InitWaypoints(150.f, m_scene->GetPlanetPosition(), 10, m_outer_waypoints);
}

void LevelManager::Update(float deltaTime, const Vector2& player_pos)
{
	if (!m_is_waiting)
		m_timer += deltaTime / 100.f;

	if (m_current_command == CommandType::SPAWN && m_timer >= m_current_timer && !m_is_complete)
	{
		//if there is available waypoint for next enemy, increase index
		if (SpawnEnemy(player_pos))
		{
			m_index++;
			//if not ends - moves to next enemy
			if (m_index < m_commands.size())
			{
				//std::cout << m_index << std::endl;
				m_current_command = m_commands[m_index]->command;
				m_current_timer = m_commands[m_index]->timer;
				m_current_enemy_type = m_commands[m_index]->id;
				m_is_waiting = false;
			}
			else
			{
				m_is_complete = true;
			}
		}
		//else, stop timer and wait until there's an available waypoint
		else
		{
			m_is_waiting = true;
		}

	}
	else if (m_current_command == CommandType::WAIT)
	{
		//checking to see if the all the previous enemies are dead
		//if not, stop the timer
		if (!AreAllEnemiesDead())
		{
			m_is_waiting = true;
		}
		//if all are dead, move to the next command
		else
		{
			m_active_enemies.clear();
			m_index++;
			//if not ends - moves to next enemy
			if (m_index < m_commands.size())
			{
				m_current_command = m_commands[m_index]->command;
				m_current_timer = m_commands[m_index]->timer;
				m_current_enemy_type = m_commands[m_index]->id;
				m_is_waiting = false;
			}
		}
	}
}

bool LevelManager::SpawnEnemy(const Vector2& player_pos)
{
	//spawn based on type
	//chase and explode enemies moves towards player
	if (m_current_enemy_type == (int)EnemyType::SlowChaseType)
	{
		//spawn enemy
		m_active_enemies.push_back(m_chase_spawner->SpawnEnemyToPos(player_pos));
	}
	//enemy that can be on defense and stays at waypoint
	else if (m_current_enemy_type == (int)EnemyType::TwoModeType)
	{
		Waypoint* destination = WaypointGenerator::GetRandomlyAvailableWaypoint(m_outer_waypoints);
		if (destination == nullptr) return false;
		m_active_enemies.push_back(m_defense_spawner->SpawnEnemyToPos(*destination));
	}
	//shoot moves to and stays at outer waypoint
	else if (m_current_enemy_type == (int)EnemyType::ShootType)
	{
		Waypoint* destination = WaypointGenerator::GetRandomlyAvailableWaypoint(m_outer_waypoints);
		if (destination == nullptr) return false;
		m_active_enemies.push_back(m_shoot_spawner->SpawnEnemyToPos(*destination));
	}
	//split type moves to random inner waypoints
	else if (m_current_enemy_type == (int)EnemyType::SplitType)
	{
		m_active_enemies.push_back(m_split_spawner->SpawnEnemy());
	}
	return true;
}

bool LevelManager::AreAllEnemiesDead()
{
	if (m_active_enemies.size() == 0) return true;
	for (const auto& enemy : m_active_enemies) 
	{
		if (enemy->IsAlive()) 
		{
			return false; //found a living enemy
		}
	}
	return true; //all enemies are dead
}

void LevelManager::Restart()
{
	//reset pool
	m_chase_pool.SetUp();
	m_shoot_pool.SetUp();
	m_split_pool.SetUp();
	m_defense_pool.SetUp();
	m_child_pool.SetUp();

	//reset timer & flags
	m_is_complete = false;
	m_is_waiting = false;
	SetUpTimer();

	//reset waypoints
	for (auto& wp : m_outer_waypoints)
	{
		wp.is_available = true;
	}

	//clear active enemies
	m_active_enemies.clear();
}

void LevelManager::SetUpTimer()
{
	m_timer = 0.f;
	m_index = 0;

	if (m_commands.size() == 0) return;
	m_current_command = m_commands[m_index]->command;
	m_current_timer = m_commands[m_index]->timer;
	m_current_enemy_type = m_commands[m_index]->id;
}

LevelManager& LevelManager::GetInstance()
{
	static LevelManager manager;
	return manager;
}