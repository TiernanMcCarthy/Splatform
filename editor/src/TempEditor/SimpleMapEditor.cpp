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
#include "TempEditor/EditorTempCamera.h"



void SimpleMapEditor::LoadTerrainFromFile()
{
    std::string path = "assets/terrain";
    for (const auto & entry : std::filesystem::directory_iterator(path))
    {

    }
}


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

    camera =(new GameObject())->AddBehaviour<EditorTempCamera>();

    //camera->Start();

    camera->gameObject->serialise=false;


    selection= new GameObject("Selection");

    selection->transform.localScale=sf::Vector2f(tileSize,tileSize);

    BoxRenderer* selectionImage= selection->AddBehaviour<BoxRenderer>();

    selectionImage->ApplyImage("assets/editor/selection.png");


    LoadTerrainFromFile();

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

void SimpleMapEditor::ManageInput()
{
    long currentTime=time(nullptr);

    if (EngineInputSystem::InputSystem->upKey->wasReleasedThisFrame ||
        EngineInputSystem::InputSystem->upKey->isPerformed && currentTime-EngineInputSystem::InputSystem->upKey->pressTime >0.3f )
    {
        posY-=1;
    }
    if (EngineInputSystem::InputSystem->downKey->wasReleasedThisFrame ||
        EngineInputSystem::InputSystem->downKey->isPerformed&& currentTime-EngineInputSystem::InputSystem->downKey->pressTime >0.3f  )
    {
        posY+=1;
    }

    if (EngineInputSystem::InputSystem->rightKey->wasReleasedThisFrame ||
        EngineInputSystem::InputSystem->rightKey->isPerformed && currentTime-EngineInputSystem::InputSystem->rightKey->pressTime >0.3f  )
    {
        posX+=1;
    }
    if (EngineInputSystem::InputSystem->leftKey->wasReleasedThisFrame ||
        EngineInputSystem::InputSystem->leftKey->isPerformed&& currentTime-EngineInputSystem::InputSystem->leftKey->pressTime >0.3f  )
    {
        posX-=1;
    }

}

void SimpleMapEditor::ManageSelection()
{

}

void SimpleMapEditor::Update(float deltaTime)
{
    //CheckStates();
    ManageInput();
    ManageSaving();
    sf::Vector2f newPos= sf::Vector2f(tileSize*posX*snapSize[currentSnap],tileSize*posY*snapSize[currentSnap]);
    camera->SetCameraPos(newPos);
    selection->transform.SetPosition(newPos);
}

