#pragma once
#include "GameObject.h"

enum class EnemyType;

namespace GameObjectFactory
{
	Object::Ref CreateEnemy(Transform& transform, EnemyType enemy_type);
	Object::Ref CreatePlayer(const Vector2& center, float distance, float scale);
	Object::Ref CreateCoin(Transform& transform);
	Object::Ref CreateBullet(float r, float b, float g, float size, int lifespan, std::string tag);
	Object::Ref CreateCombatPlanet(const Vector2& center_position, float radius);
	Object::Ref CreateShootEnemySpawner(const Vector2& spanw_pos);
	Object::Ref CreateChaseEnemySpawner(const Vector2& spanw_pos);
};