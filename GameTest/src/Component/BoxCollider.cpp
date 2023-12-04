#include "stdafx.h"
#include "BoxCollider.h"
#include "Transform.h"
//
#include "GameObject/GameObject.h"
#include "System/Scene.h"
#include "System/CollisionManager.h"

BoxCollider::BoxCollider(std::string tag) : size(Vector2{0.f}), position(Vector2{0.f}), tag(tag), transform(nullptr) {}

BoxCollider::BoxCollider(std::string tag, Vector2& size) : size(size), position(Vector2{ 0.f }), tag(tag), transform(nullptr) {}

//BoxCollider::BoxCollider(std::string tag, Vector2& size, CollisionManager& manager) : size(size), position(Vector2{ 0.f }), tag(tag), transform(nullptr), collision_manager(&manager) {}

void BoxCollider::Init()
{
    transform = &Component::object->GetComponent<Transform>();
    SetPosition(transform->position.x, transform->position.y);

    //add itself to the collider vectors when one is created
    CollisionManager::GetInstance().AddToColliders(*this);
}

void BoxCollider::Update(float deltaTime)
{
    SetPosition(transform->position.x, transform->position.y);

}

void BoxCollider::Render()
{
    //Debug();
}

void BoxCollider::Debug()
{
    //draw a debug collider box
    App::DrawLine(position.x, position.y, position.x + size.x, position.y, 1.f, 0.f, 0.f);
    App::DrawLine(position.x, position.y, position.x, position.y + size.y, 1.f, 0.f, 0.f);

    App::DrawLine(position.x, position.y + size.y, position.x + size.x, position.y + size.y, 1.f, 0.f, 0.f);
    App::DrawLine(position.x + size.x, position.y, position.x + size.x, position.y + size.y, 1.f, 0.f, 0.f);
}

void BoxCollider::SetPosition(float x, float y)
{
    position.x = x - size.x / 2;
    position.y = y - size.y / 2;
}

bool BoxCollider::AABBCheck(BoxCollider& other_collider) const
{
    //The sides of the rectangles
    float leftA, leftB;
    float rightA, rightB;
    float topA, topB;
    float bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = position.x;
    rightA = position.x + size.x;
    bottomA = position.y;
    topA = position.y + size.y;

    //Calculate the sides of rect B
    leftB = other_collider.position.x;
    rightB = other_collider.position.x + other_collider.size.x;
    bottomB = other_collider.position.y;
    topB = other_collider.position.y + other_collider.size.y;

    //If any of the sides from A are outside of B

    if (bottomA > topB)
    {
        return false;
    }

    if (topA < bottomB)
    {
        return false;
    }

    if (rightA < leftB)
    {
        return false;
    }

    if (leftA > rightB)
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}