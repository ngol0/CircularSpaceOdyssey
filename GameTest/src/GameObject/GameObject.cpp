#include "stdafx.h"
#include "GameObject.h"
#include "Component/Transform.h"

GameObject::GameObject()
{
	GameObject::AddComponent<Transform>(Vector2(0.f, 0.f), 1.f);
}

GameObject::GameObject(Transform& transform)
{
	GameObject::AddComponent<Transform>(transform.position, transform.scale);
}

void GameObject::Update(float deltaTime)
{
	for (auto& component : m_component_list)
	{
		component->Update(deltaTime);
	}
}

void GameObject::Render()
{
	for (auto& component : m_component_list)
	{
		component->Render();
	}
}

void GameObject::Deactivate()
{
	b_alive = false;
}

void GameObject::Activate()
{
	b_alive = true;
}

void GameObject::SetPosition(const Vector2& position)
{
	GetComponent<Transform>().position = position;
}

void GameObject::SetRotationAngle(float rotation)
{
	GetComponent<Transform>().rotation_angle = rotation;
}

void GameObject::SetScale(const float& scale)
{
	GetComponent<Transform>().scale = scale;
}

void GameObject::SetForwardVector(const Vector2& forward_vector)
{
	GetComponent<Transform>().forward = forward_vector;
}
