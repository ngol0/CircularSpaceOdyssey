/*This struct is to be inherited by all the specific components*/
#pragma once
class GameObject;

struct Component
{
	std::string name;
	GameObject* object{ nullptr };

	Component() {};
	virtual ~Component() {};

	virtual void Init() {};
	virtual void Update(float deltaTime) {};
	virtual void Render() {};
};

