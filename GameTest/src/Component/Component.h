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
	virtual void Restart() {};
};

