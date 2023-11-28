#include "stdafx.h"
#include "CollisionManager.h"
#include "Component/BoxCollider.h"
#include "GameObject/GameObject.h"

CollisionManager::CollisionManager() {}

bool CollisionManager::IsCollided(BoxCollider& main, BoxCollider& other)
{
	return (main.AABBCheck(other));
}

void CollisionManager::AddToColliders(BoxCollider& collider)
{
	colliders.push_back(&collider);
}

void CollisionManager::Update(float deltaTime)
{
	for (size_t i = 0; i < colliders.size(); ++i)
	{
		for (size_t j = i + 1; j < colliders.size(); ++j)
		{
			if (!colliders[i]->object->IsAlive() || !colliders[j]->object->IsAlive()) continue;
			if (colliders[i]->tag == colliders[j]->tag) continue;
			
			bool current_collision_status = IsCollided(*colliders[i], *colliders[j]);

			auto key = std::make_pair(colliders[i], colliders[j]);

			// Check if the collision status has changed from the previous frame
			// If they have
			if (current_collision_status != collision_map[key])
			{
				// If two are collided -> on collision enter
				if (current_collision_status)
				{
					std::cout << "On collision enter" << std::endl;
					colliders[i]->collision_enter.Notify(*colliders[j]);
					colliders[j]->collision_enter.Notify(*colliders[i]);

					colliders[i]->collisions_enter.Notify(*colliders[i], *colliders[j]);
					colliders[j]->collisions_enter.Notify(*colliders[j], *colliders[i]);
				}
				// If two are not collided -> on collision exit
				else
				{
					std::cout << "On collision exit" << std::endl;
					colliders[i]->collision_exit.Notify(*colliders[j]);
					colliders[j]->collision_exit.Notify(*colliders[i]);
				}

				// Update the collision map with the current status
				collision_map[key] = current_collision_status;
			}
			// If status hasn't changed and they were collided on last frame, on collision stay 
			else if (current_collision_status == collision_map[key] && current_collision_status)
			{
				std::cout << "On collision stay" << std::endl;
				colliders[i]->collision_stay.Notify(*colliders[j]);
				colliders[j]->collision_stay.Notify(*colliders[i]);
			}
		}
	}
}