#pragma once
#include "GameObject.h"

class Scene;

namespace GameObjectFactory
{
	Core::Ref CreateEnemy(Transform& transform, Scene& scene);
	Core::Ref CreatePlayer(const Vector2& center, float distance, float scale, Scene& scene);
	Core::Ref CreateCoin(Transform& transform, Scene& scene);
	Core::Ref CreateBullet(Scene& scene);
	Core::Ref CreateCircle(const Vector2& center_position, float radius, Scene& scene);
};