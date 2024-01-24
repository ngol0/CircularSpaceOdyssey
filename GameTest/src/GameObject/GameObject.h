/* A generic game object class
* Acts as a collection of components
* With methods to add/get components (max components is 32)
* and update/render all of them
*/
#pragma once
#include "Component/Component.h"
#include "Math/Vector2.h"
#include "Global/Event.h"
#include <array>
#include <cassert>
#include <bitset>

constexpr size_t MAX_COMPONENTS = 32;
using ComponentID = std::size_t;
using ComponetBitMask = std::bitset<MAX_COMPONENTS>;
using ComponentArray = std::array<Component*, MAX_COMPONENTS>;

class Transform;

class GameObject
{
private:
	bool b_alive{ true };

	std::vector<std::unique_ptr<Component>> m_component_list;
	ComponetBitMask m_component_bitmask;
	ComponentArray m_component_arr;

public:
	GameObject();
	GameObject(Transform& transform);
	~GameObject() {};
	void Init() {};
	void Update(float deltaTime);
	void Render();

	bool IsAlive() const { return b_alive; }
	void Deactivate();
	void Activate();

	//set object's transform values
	void SetPosition(const Vector2& position);
	void SetRotationAngle(float rotation);
	void SetScale(const float& scale);
	void SetForwardVector(const Vector2& forward_vector);

	//check if the object has a certain component
	template<typename T>
	bool HasComponent() const
	{
		return m_component_bitmask.test(GetComponentId<T>());
	}

	//method to add component to the game object
	//T is the component type, TArgs is a parameter used to construct the component
	template<typename T, typename... TArgs>
	T& AddComponent(TArgs&&...m_args)
	{
		//make sure the component has not been added before
		assert(!HasComponent<T>());

		//allocating the component type T on the heap
		//and forward the passed arguments to its constructor
		T* component = new T(std::forward<TArgs>(m_args)...);
		
		//set the object that holds the component
		component->object = this;

		//use unique pointer so that it manages the obj's lifetime
		std::unique_ptr<Component> comp_uPtr{ component };
		m_component_list.emplace_back(std::move(comp_uPtr));

		//add to array and bitmask
		m_component_bitmask.set(GetComponentId<T>());
		m_component_arr[GetComponentId<T>()] = component;

		//call component init in which each component will get the other component or data it needs
		component->Init();

		return *component;
	}

	//method to get the wanted component
	template<typename T>
	T& GetComponent()
	{
		assert(HasComponent<T>());

		auto component_ptr = m_component_arr[GetComponentId<T>()];
		return *static_cast<T*>(component_ptr);
	}
};

inline ComponentID GetUniqueComponentID()
{
	static ComponentID lastID{ 0u };
	return lastID++;
}

/* Returns a unique ID the first time it's called with a new component
then returns the same ID for the same component */
template <class T>
inline ComponentID GetComponentId()
{
	static ComponentID typeID = GetUniqueComponentID();
	return typeID;
}

namespace Object
{
	using Ref_List = std::vector<std::shared_ptr<GameObject>>;
	using Ref = std::shared_ptr<GameObject>;
}
