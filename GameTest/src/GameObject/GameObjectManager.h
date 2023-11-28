#pragma once
#include "GameObject.h"

using ObjectList = std::vector<std::unique_ptr<GameObject>>;

class GameObjectManager
{
private:
	ObjectList object_list;

public:
	GameObjectManager() {};
	~GameObjectManager() {};

	void Init(){};
	void Update(float deltaTime);
	void Render();

	void Restart();

	GameObject& AddToManager();
	GameObject& AddToManager(Transform& transform);
};