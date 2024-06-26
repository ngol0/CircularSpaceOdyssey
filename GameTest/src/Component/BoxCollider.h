/* Box collider using AABB check */
#pragma once
#include "Component.h"
#include "Math/Vector2.h"
#include "Global/Event.h"

class Scene;

class BoxCollider : public Component
{
public:
	BoxCollider(std::string tag);
	BoxCollider(std::string tag, Vector2& size);

	bool AABBCheck(BoxCollider& other_collider) const;
	void SetPosition(float x, float y);

	void Init() override;
	void Update(float deltaTime) override;
	void Render() override;

	Vector2 size;
	Vector2 position;

	std::string tag;
	class Transform* transform;

	bool is_debug{ false };

	Event<Scene, BoxCollider&> collision_enter;
	Event<Scene, BoxCollider&, BoxCollider&> collisions_enter;

	Event<Scene, BoxCollider&> collision_stay;
	Event<Scene, BoxCollider&> collision_exit;
};
