//
// Created by tiernux on 27/12/2025.
//
#include "../../include/CollisionTests/ColliderDebug.h"

#include "BoxRenderer.h"
#include "Constants.h"
#include "EngineInputSystem.h"
#include "Objects/GameObject.h"
#include "AABB.h"
#include "CollisionTests/AABBTestClass.h"
#include "Gizmos/GizmoManager.h"

REGISTER_BEHAVIOUR(ColliderDebug);
void ColliderDebug::Start()
{
    //gameObject->transform.localScale=sf::Vector2<float>(100,100);

    //Create and position this GameObject
    ourCollider=gameObject->AddBehaviour<AABB>();





    gameObject->transform.localScale=sf::Vector2<float>(100,100);

   // gameObject->transform.SetPosition(DISPLAYWIDTH/1.4f,DISPLAYHEIGHT/2);

    ourCollider->SetHalfSize(sf::Vector2f(50,50));

    renderer=gameObject->AddBehaviour<BoxRenderer>();

   // renderer->color=sf::Color::Cyan;

    renderer->ApplyImage("assets/flatimage.png");
    renderer->depth=1;

    collisionDot= (new GameObject("CollisionDot"))->AddBehaviour<BoxRenderer>();;

    collisionDot->color=sf::Color::Yellow;
    collisionDot->depth=1;

    collisionDot->gameObject->transform.localScale=sf::Vector2<float>(15,15);

    boxVbox = (new GameObject("BoxVBox"))->AddBehaviour<AABBTestClass>();

    // Get a different random number each time the program runs
    srand(time(0));
}

void ColliderDebug::Update(float deltaTime)
{

    sf::Vector2f point=EngineInputSystem::WorldSpaceMousePos();


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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G))
    {
        moveSpeed+=50;
        std::cout<<moveSpeed<<std::endl;
    }
    sf::Vector2f pos=gameObject->transform.GetPosition() + sf::Vector2f(x,y);



    gameObject->transform.SetPosition(pos);



    //AABB vs  Point
    HitResult result=ourCollider->IntersectPoint(point);
    if (result.debugHit)
    {
        renderer->color=sf::Color::Red; //gameObject->transform.GetPosition()+result.delta
        renderer->depth=1;
        collisionDot->gameObject->transform.SetPosition(result.hitPosition);
    }
    else
    {
        renderer->color=sf::Color::Cyan;

        collisionDot->gameObject->transform.SetPosition(5000,5000);
    }

    //AABB vs Segment

    sf::Vector2f dir =EngineInputSystem::WorldSpaceMousePos()-sf::Vector2f(DISPLAYWIDTH/2,DISPLAYHEIGHT/2);

    result = ourCollider->IntersectSegment(sf::Vector2f(DISPLAYWIDTH/2,DISPLAYHEIGHT/2),dir);

    if (result.debugHit==true) //Short line of penetrating segment
    {
        GizmoManager::Colour=sf::Color::Blue;
        GizmoManager::DrawLine(result.hitPosition,result.hitPosition-(result.delta),5);
        GizmoManager::Colour=sf::Color::Yellow;
        GizmoManager::DrawLine(sf::Vector2f(DISPLAYWIDTH/2,DISPLAYHEIGHT/2),result.hitPosition,5);
    }
    else
    {
        GizmoManager::Colour=sf::Color::Green;
        GizmoManager::DrawLine(sf::Vector2f(DISPLAYWIDTH/2,DISPLAYHEIGHT/2),EngineInputSystem::WorldSpaceMousePos(),5);
    }
    GizmoManager::Colour=sf::Color::Yellow;
    //GizmoManager::DrawLine(gameObject->transform.GetPosition(),EngineInputSystem::WorldSpaceMousePos(),5);

    //AABB vs AABB

    result = ourCollider->IntersectAABB(boxVbox->collider);
    if (result.debugHit==true)
    {
        boxVbox->renderer->color=sf::Color::Green;
        boxVbox->renderer->UpdateVisualComponents();

        sf::Vector2f newPos=gameObject->transform.GetPosition() + result.delta;

        gameObject->transform.SetPosition(newPos);

    }
    else
    {
        boxVbox->renderer->color=sf::Color::Red;
        boxVbox->renderer->UpdateVisualComponents();
    }






    renderer->UpdateVisualComponents();
}

void ColliderDebug::OnDestroy()
{
    std::cout<<"ColliderDebug::OnDestroy"<<std::endl;
}


