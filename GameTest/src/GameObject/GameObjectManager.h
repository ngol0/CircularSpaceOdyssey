#pragma once
#include "GameObject.h"

class GameObjectManager
{
private:
	Object::Ref_List object_container;

	GameObjectManager() {};
	GameObjectManager(const GameObjectManager&) = delete; //avoid copy constructor

public:
	void Init(){};
	void Update(float deltaTime);
	void Render();

	void Reactivate();

	Object::Ref AddToManager(Transform& transform);
	Object::Ref AddToManager();

	//singleton
	static GameObjectManager& GetInstance();
};