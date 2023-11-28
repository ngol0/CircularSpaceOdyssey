#pragma once
#include "GameObject.h"

class Scene;

namespace GameObjectFactory
{
	GameObject& CreatePlayer(float scale, Scene& scene);
	GameObject& CreateCoin(Transform& transform, Scene& scene);
	GameObject& CreateEnemy(Transform& transform, Scene& scene);
	GameObject& CreateBullet(GameObject& object, Scene& scene);
	GameObject& CreateCircle(const Vector2& center_position, float radius, Scene& scene);
};