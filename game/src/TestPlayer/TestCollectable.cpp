//
// Created by tiernux on 25/02/2026.
//
#include "TestPlayer/TestCollectable.h"

#include "Objects/GameObject.h"
#include "TestPlayer/TestPlayer.h"

void TestCollectable::Start()
{
    collider= gameObject->AddBehaviour<AABB>();
    renderer= gameObject->AddBehaviour<BoxRenderer>();

    gameObject->transform.localScale=sf::Vector2f{20,20};
    player=SceneManagement::GetBehaviourOfType<TestPlayer>();
}

void TestCollectable::Collect()
{

}

void TestCollectable::Update(float deltaTime)
{

    if (collider->IntersectAABB(player->collider).debugHit)
    {

    }

}