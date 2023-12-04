#pragma once
#include "GameObject.h"

namespace GameObjectFactory
{
	Object::Ref CreateEnemy(Transform& transform);
	Object::Ref CreatePlayer(const Vector2& center, const float& distance, const float& scale);
	Object::Ref CreateCoin(Transform& transform);
	Object::Ref CreateBullet();
	Object::Ref CreateCombatPlanet(const Vector2& center_position, const float& radius);
};