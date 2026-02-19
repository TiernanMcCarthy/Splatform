//
// Created by Tiern on 19/02/2026.
//
#include "TestPlayer/PlayerSpawn.h"

#include "BoxRenderer.h"
#include "Objects/GameObject.h"

REGISTER_BEHAVIOUR(PlayerSpawn)

void PlayerSpawn::Start()
{
    gameObject->transform.localScale=sf::Vector2f(80,80);
    BoxRenderer* renderer= gameObject->AddBehaviour<BoxRenderer>();

    renderer->ApplyImage("assets/StartFlag.png");
}
