//
// Created by tiernux on 01/01/2026.
//
#include "CollisionTests/AABBTestClass.h"
#include "BoxRenderer.h"
#include "Constants.h"
#include "AABB.h"

void AABBTestClass::Start()
{
    //Create and position this GameObject
    collider=gameObject->AddBehaviour<AABB>();

    gameObject->transform.localScale=sf::Vector2<float>(100,400);

    gameObject->transform.SetPosition(DISPLAYWIDTH/1.8f,DISPLAYHEIGHT/2);

    collider->halfSize=sf::Vector2f(50,200);

    renderer=gameObject->AddBehaviour<BoxRenderer>();
}
