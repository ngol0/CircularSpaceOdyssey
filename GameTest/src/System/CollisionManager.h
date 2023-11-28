#pragma once
#include <map>

struct BoxCollider;

class CollisionManager
{
private:
	std::vector<BoxCollider*> colliders;
	std::map<std::pair<BoxCollider*, BoxCollider*>, bool> collision_map;

public:
	CollisionManager();
	~CollisionManager() {};

	bool IsCollided(BoxCollider& main, BoxCollider& other);
	void AddToColliders(BoxCollider& collider);

	void Init() {};
	void Update(float deltaTime);
};