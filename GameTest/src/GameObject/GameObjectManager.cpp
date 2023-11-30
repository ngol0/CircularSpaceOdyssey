#include "stdafx.h"
#include "GameObjectManager.h"
#include "Component/BoxCollider.h"


Core::Ref GameObjectManager::AddToManager(Transform& transform)
{
	Core::Ref obj_ref = std::make_shared<GameObject>(transform);
	object_container.emplace_back(std::move(obj_ref));

	return object_container.back();
}

Core::Ref GameObjectManager::AddToManager()
{
	Core::Ref obj_ref = std::make_shared<GameObject>();
	object_container.emplace_back(std::move(obj_ref));

	return object_container.back();
}

void GameObjectManager::Update(float deltaTime)
{
	for (auto& object : object_container)
	{
		if (!object->IsAlive()) continue;
		object->Update(deltaTime);
	}
}

void GameObjectManager::Render()
{
	for (auto& object : object_container)
	{
		if (!object->IsAlive()) continue;
		object->Render();
	}
}

void GameObjectManager::Reactivate()
{
	for (auto& object : object_container)
	{
		object->Activate();
	}
}
