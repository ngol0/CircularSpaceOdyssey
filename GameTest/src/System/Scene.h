#pragma once
#include "Component/BoxCollider.h"
#include "Component/Health.h"
#include "Component/Transform.h"
#include "GameObject/GameObject.h"
#include "GameObject/ParticlePool.h"

class Scene
{
public:
	Scene();

	void Init();
	void Update(float deltaTime);
	void Render();
	void Shutdown() {};
	void SetUp();
	void Restart();
	void OnEnemyDie(const Vector2& pos);
	void OnGameOver(const Vector2& pos);

	//getters
	int GetPlayerHealth() const { return m_player->GetComponent<Health>().health_amount; }
	int GetScore() const { return m_score; }
	const Vector2& GetPlayerPos() const { return m_player->GetComponent<Transform>().position; }
	const Vector2& GetPlanetPosition() const { return m_circle_center; }

	//event callback
	void OnPlayerCollisionEnter(BoxCollider& other);
	void OnEnemyCollisionEnter(BoxCollider& enemy, BoxCollider& bullet);

private:
	Object::Ref m_player;
	Object::Ref m_planet;

	//planet
	Vector2 m_circle_center;
	float m_circle_radius;

	//general datas
	int m_score;

	//particles
	ParticlePool m_explosion_particle_pool;
};

