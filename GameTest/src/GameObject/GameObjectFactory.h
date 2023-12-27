#pragma once
#include "GameObject.h"

enum class EnemyType;

namespace GameObjectFactory
{
	Object::Ref CreateEnemy(Transform& transform, EnemyType enemy_type);
	Object::Ref CreatePlayer(const Vector2& center, float distance, float scale);
	Object::Ref CreateCoin(Transform& transform);
	Object::Ref CreateBullet(float r, float g, float b, float size, int lifespan, std::string tag);
	Object::Ref CreateCombatPlanet(const Vector2& center_position, float radius);
	Object::Ref CreateEnemySpawner(const Vector2& spanw_pos);
	//Object::Ref CreateParticle();
};