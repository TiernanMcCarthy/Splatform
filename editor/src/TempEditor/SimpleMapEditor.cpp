//
// Created by Tiern on 19/02/2026.
//
#include "TempEditor/SimpleMapEditor.h"

#include <TestPlayer/TestPlayer.h>

#include "EngineInputSystem.h"
#include "Objects/GameObject.h"
#include "SceneCamera.h"
#include "BoxRenderer.h"
#include "Constants.h"

void SimpleMapEditor::Start()
{
    lastObject=nullptr;

    isCreating=false;

    gameObject->serialise=false;

    spawnPoint= (new GameObject())->AddBehaviour<PlayerSpawn>();

    player = (new GameObject("TestPlayer"))->AddBehaviour<TestPlayer>();

    player->Start();

    player->isActive=false;

    BoxRenderer* background = (new GameObject("background"))->AddBehaviour<BoxRenderer>();

    background->ApplyImage("assets/greenhill.png");

    background->gameObject->transform.SetPosition(DISPLAYWIDTH/2,DISPLAYHEIGHT/2);

    background->gameObject->transform.localScale=sf::Vector2f(3840*4,256*4);


    SceneCamera* tempCamera =(new GameObject())->AddBehaviour<SceneCamera>();

    //tempCamera->gameObject->serialise=false;


}

void SimpleMapEditor::FinishBlock()
{

    lastObject=currentContext;
    currentContext=nullptr;

    isCreating=false;



}


void SimpleMapEditor::BuildBlock()
{

    sf::Vector2f mousePos = EngineInputSystem::WorldSpaceMousePos();

    sf::Vector2f centerPos = (spawnPos + mousePos) / 2.0f;

    float width = std::abs(mousePos.x - spawnPos.x);
    float height = std::abs(mousePos.y - spawnPos.y);

    currentContext->gameObject->transform.SetPosition(centerPos);
    currentContext->gameObject->transform.localScale = sf::Vector2f(width, height);
}


void SimpleMapEditor::CreateBlock()
{
    currentContext = (new GameObject("TerrainBlock"))->AddBehaviour<RectangleBlock>();

    spawnPos=EngineInputSystem::WorldSpaceMousePos();

    currentContext->gameObject->transform.SetPosition(spawnPos);

}


void SimpleMapEditor::CheckStates()
{
    if (EngineInputSystem::InputSystem->MouseOne->wasFirstPerformedThisFrame)
    {
        isCreating=true;
        CreateBlock();
    }
    else if (EngineInputSystem::InputSystem->MouseOne->wasReleasedThisFrame)
    {
        isCreating=false;
        FinishBlock();
    }

    if (isCreating)
    {
        BuildBlock();
    }

    if (EngineInputSystem::InputSystem->pKey->wasReleasedThisFrame)
    {
        spawnPoint->gameObject->transform.SetPosition(EngineInputSystem::WorldSpaceMousePos());
    }

    if (EngineInputSystem::InputSystem->MouseTwo->wasReleasedThisFrame) {
        player->gameObject->transform.SetPosition(EngineInputSystem::WorldSpaceMousePos());
    }

}


void SimpleMapEditor::ManageSaving()
{
    if (EngineInputSystem::InputSystem->eKey->wasReleasedThisFrame)
    {
        player->gameObject->isActive=true;
        SceneManagement::SaveCurrentScene();

    }
}



void SimpleMapEditor::Update(float deltaTime)
{
    CheckStates();
    ManageSaving();
}

