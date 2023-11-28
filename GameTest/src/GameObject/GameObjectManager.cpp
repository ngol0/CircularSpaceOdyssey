#include "stdafx.h"
#include "GameObjectManager.h"
#include "Component/BoxCollider.h"


GameObject& GameObjectManager::AddToManager()
{
	GameObject* object = new GameObject();
	std::unique_ptr<GameObject> obj_uPtr{ object };
	object_list.emplace_back(std::move(obj_uPtr));

	return *object;
}

GameObject& GameObjectManager::AddToManager(Transform& transform)
{
	GameObject* object = new GameObject(transform);
	std::unique_ptr<GameObject> obj_uPtr{ object };
	object_list.emplace_back(std::move(obj_uPtr));

	return *object;
}

void GameObjectManager::Update(float deltaTime)
{
	for (auto& object : object_list)
	{
		if (!object->IsAlive()) continue;
		object->Update(deltaTime);
	}
}

void GameObjectManager::Render()
{
	for (auto& object : object_list)
	{
		if (!object->IsAlive()) continue;
		object->Render();
	}
}

void GameObjectManager::Restart()
{
	for (auto& object : object_list)
	{
		object->Restart();
	}
}
