#pragma once
#include <SFML/System.hpp>
#include <vector>
#include "Object.h"
#include <unordered_map>
#include <memory>
#include <typeinfo>
#include <typeindex>
#include "Engine.h"
#include <algorithm>
class Behaviour;

struct Transform
{
public:
	sf::Vector2f localPosition;
	sf::Vector2f localRotation;
	sf::Vector2f localScale;

	Transform* parent = nullptr;

	Transform()
	{
		localPosition = sf::Vector2f(0, 0);
		localRotation = sf::Vector2f(0, 0);
		localScale = sf::Vector2f(1, 1);
		children = std::vector<Transform*>();
	}

	void SetLocalPosition(sf::Vector2f position)
	{
		localPosition = position;
	}

	sf::Vector2f GetLocalPosition(sf::Vector2f position)
	{
		return localPosition;
	}

	/// <summary>
	/// Set World Position in respect to any parent
	/// </summary>
	/// <param name="worldPos"></param>
	void SetPosition(sf::Vector2f worldPos)
	{
		if (parent != nullptr)
		{
			localPosition = worldPos - parent->GetPosition();
		}
		else
		{
			localPosition = worldPos;
		}
	}

	void SetPosition(float x, float y)
	{
		sf::Vector2<float> worldPos = sf::Vector2<float>(x, y);
		if (parent != nullptr)
		{
			localPosition = worldPos - parent->GetPosition();
		}
		else
		{
			localPosition = worldPos;
		}
	}

	/// <summary>
	/// Get world position
	/// </summary>
	/// <returns></returns>
	sf::Vector2f GetPosition()
	{
		if (parent != nullptr)
		{
			return parent->GetPosition() + localPosition;
		}
		else
		{
			return localPosition;
		}
	}

	void AddChild(Transform* child)
	{
		if (child != nullptr && child != this)
		{
			children.push_back(child);
			child->parent = this;
		}
	}

	void RemoveChild(Transform* child)
	{
		if (child == nullptr)
		{
			return;
		}
		children.erase(std::remove(children.begin(), children.end(), child),children.end());

		if (child->parent == this)
		{
			child->parent = nullptr;
		}
	}

	void SetParent(Transform* newParent)
	{
		if (parent != nullptr)
		{
			parent->RemoveChild(this);
		}
		else if(newParent!=nullptr)
		{
			newParent->AddChild(this);
		}
	}

private:
	std::vector<Transform*> children;
};

/// <summary>
/// GameObjects exist to manage transforms, they can be spawned and destroyed;
/// </summary>
/// 
class GameObject : public Object
{

public:

	bool isActive = true;

	std::string name;

	Transform transform;

	GameObject(std::string objectname="GameObject");

	~GameObject();

	virtual void Update(float deltaTime);

    virtual void FixedUpdate(float fixedDeltaTime);

	virtual void Render();

	virtual void UpdateTransform();

	virtual void Start();

	void OnDestroy() override;

	template<typename T, typename... Args>
	T* AddBehaviour(Args&&... args) {
		static_assert(std::is_base_of<Behaviour, T>::value, "T must inherit Behaviour");

		T* behaviour = new T(std::forward<Args>(args)...);
		behaviour->SetGameObject(this);
		behaviours.push_back(behaviour);
		behaviour->Start();

		return behaviour; 
	}

	template<typename T>
	T* GetBehaviour() {
		for (auto b : behaviours) {
			if (typeid(*b) == typeid(T)) {
				return static_cast<T*>(b);
			}
		}
		return nullptr;
	}

	void RemoveBehaviour(Behaviour* b);
private:

	std::vector<Behaviour*> behaviours;

	void SetBehaviourParent(Behaviour* b);

	
};

