/* Create all the specific game objects in the game (i.e: player, enemies, etc.)
* by creating a general game object and then adding the suitable components to each of them
*/
#pragma once
#include "GameObject.h"

enum class EnemyType;
enum class PowerUpType;
enum class ParticleType;

namespace GameObjectFactory
{
	Object::Ref CreateEnemy(Transform& transform, EnemyType enemy_type);
	Object::Ref CreatePlayer(const Vector2& center, float distance, float scale);
	Object::Ref CreatePowerUp(PowerUpType powerup_type);
	Object::Ref CreateBullet(float r, float g, float b, float size, int lifespan, float speed, std::string tag);
	Object::Ref CreateCombatPlanet(const Vector2& center_position, float radius, int steps);
	Object::Ref CreateEnemySpawner(const Vector2& spanw_pos);
	Object::Ref CreateParticle(float r, float g, float b, float size, float lifespan, ParticleType type);
};