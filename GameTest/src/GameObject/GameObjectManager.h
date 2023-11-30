#pragma once
#include "GameObject.h"

class GameObjectManager
{
private:
	Core::Ref_List object_container;

public:
	GameObjectManager() {};
	~GameObjectManager() {};

	void Init(){};
	void Update(float deltaTime);
	void Render();

	void Reactivate();

	Core::Ref AddToManager(Transform& transform);
	Core::Ref AddToManager();
};