/* This class's responsibility is to manage all the game objects' update/rendering process in the game
* Once the game object is created through the factory, it will be added to the manager
* Then in every update and rendering call it will loop through all the game objects 
* and check if they are currently activated, if no, skip those, if yes call their update/rendering functions
*/
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