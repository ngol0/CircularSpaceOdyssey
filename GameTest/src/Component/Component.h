/*This struct is to be inherited by all the specific components
* It has the pointer to the gameobject that holds the component
* A component contains both data and logic for that specific component
* and has its own Update & Render functions
*/
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

