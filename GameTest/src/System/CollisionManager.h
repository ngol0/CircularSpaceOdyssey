/* Detect collision between two box colliders
* Once there's collision detected, it will send an event to notify listerners
*/
#pragma once
#include <map>

class BoxCollider;

class CollisionManager
{
private:
	std::vector<BoxCollider*> colliders;
	std::map<std::pair<BoxCollider*, BoxCollider*>, bool> collision_map;

	CollisionManager() {};
	CollisionManager(const CollisionManager&) = delete; //avoid copy constructor

public:
	bool IsCollided(BoxCollider& main, BoxCollider& other);
	void AddToColliders(BoxCollider& collider);

	void Init() {};
	void Update(float deltaTime);

	//singleton
	static CollisionManager& GetInstance();
};