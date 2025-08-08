//
// Created by tiernan on 7/3/25.
//
#include "../../include/UI/Button.h"

#include "../../include/Objects/GameObject.h"
#include "EngineInputSystem.h"

Button::Button()
{
    OnPress = FunctionSubscriber();
    //collider.
}

Button::~Button()
{

}


void Button::Start()
{
    collider = gameObject->AddBehaviour<AABBCollider>();

    //collider.
}

void Button::ManageButton()
{
    //Check for collision

    if (EngineInputSystem::InputSystem->MouseOne->wasReleasedThisFrame)
    {
        sf::Vector2<float> pos;
        if (worldSpace)
        {
            pos=EngineInputSystem::WorldSpaceMousePos();
        }
        else
        {
            pos=(sf::Vector2<float>)sf::Mouse::getPosition(Engine::GEngine->GetRenderWindow());
        }

        if (collider->IsPosInside(pos))
        {
            OnPress.Activate();
        }
    }
}

void Button::Update(float deltaTime)
{
    ManageButton();
}




