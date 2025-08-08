#pragma once
#include "Object.h"
#include <SFML/Graphics.hpp>
class GameObject;
/// <summary>
/// Version of a Component Or Adjacent to Unity Monobehaviour
/// </summary>
class Behaviour :public Object{
public:

    bool isEnabled = true;
    GameObject* gameObject = nullptr;

    virtual ~Behaviour() = default;

    void OnDestroy() override;

    // Called after being added to a gameobject
    virtual void Start();

    //Main Update of a behaviour, once per frame
    virtual void Update(float deltaTime);

    // Set the parent GameObject pointer
    void SetGameObject(GameObject* parent) {
        gameObject = parent;
    }
};