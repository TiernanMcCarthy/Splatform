#pragma once

#include "../AABBCollider.h"
#include "../Objects/Behaviour.h"
#include "../Systems/FunctionSubscriber.h"
class Button : public Behaviour
{
public:

    ///On press event system, subscribe to this for functionality
    FunctionSubscriber OnPress;

    bool worldSpace=true;

    Button();

    ~Button();

    void Start() override;

    void Update(float deltaTime) override;

private:
    AABBCollider* collider;

    void ManageButton();

};