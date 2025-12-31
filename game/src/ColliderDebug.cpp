//
// Created by tiernux on 27/12/2025.
//
#include "ColliderDebug.h"

#include "BoxRenderer.h"
#include "Constants.h"
#include "EngineInputSystem.h"
#include "Objects/GameObject.h"
#include "AABB.h"
#include "Gizmos/GizmoManager.h"


void ColliderDebug::Start()
{
    ourCollider=gameObject->AddBehaviour<AABB>();

    gameObject->transform.localScale=sf::Vector2<float>(100,100);

    gameObject->transform.SetPosition(DISPLAYWIDTH/2,DISPLAYHEIGHT/2);

    ourCollider->halfSize=sf::Vector2f(50,50);

    renderer=gameObject->AddBehaviour<BoxRenderer>();

    collisionDot= (new GameObject("CollisionDot"))->AddBehaviour<BoxRenderer>();;

    collisionDot->color=sf::Color::Yellow;

    collisionDot->gameObject->transform.localScale=sf::Vector2<float>(15,15);
}

void ColliderDebug::Update(float deltaTime)
{
    sf::Vector2f point=EngineInputSystem::WorldSpaceMousePos();

    HitResult result=ourCollider->IntersectPoint(point);
    if (result.debugHit)
    {
        renderer->color=sf::Color::Red; //gameObject->transform.GetPosition()+result.delta
        collisionDot->gameObject->transform.SetPosition(result.hitPosition);
    }
    else
    {
        renderer->color=sf::Color::Green;

        collisionDot->gameObject->transform.SetPosition(5000,5000);
    }
    float x=0;
    float y=0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        y-=moveSpeed*deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        y+=moveSpeed*deltaTime;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        x-=moveSpeed*deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        x+=moveSpeed*deltaTime;
    }
    sf::Vector2f pos=gameObject->transform.GetPosition() + sf::Vector2f(x,y);
    gameObject->transform.SetPosition(pos);

    GizmoManager::DrawLine(gameObject->transform.GetPosition(),EngineInputSystem::WorldSpaceMousePos(),5);


    renderer->UpdateVisualComponents();
}
