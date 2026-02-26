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
#include "TempEditor/ButtonFunctionality.h"
#include "TempEditor/SceneObject.h"



SimpleMapEditor* SimpleMapEditor::instance = nullptr;

void SimpleMapEditor::LoadTerrainFromFile()
{
    std::string path = "assets/terrain";
    int iterator =0;
    for (const auto & entry : std::filesystem::directory_iterator(path))
    {
        SceneObject* newObject= (new GameObject())->AddBehaviour<SceneObject>();

        newObject->Init(entry.path());

        newObject->gameObject->transform.SetPosition(DISPLAYWIDTH*0.025f,200+iterator*128);

        iterator++;
    }
}


void SimpleMapEditor::Start()
{
    lastObject=nullptr;

    instance=this;

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

    selection->serialise=false;

    BoxRenderer* selectionImage= selection->AddBehaviour<BoxRenderer>();

    selectionImage->depth=100;

    selectionImage->ApplyImage("assets/editor/selection.png");


    //UI

    LoadTerrainFromFile();

    editorButtons= (new GameObject("editorButtons"))->AddBehaviour<ButtonFunctionality>();

    editorButtons->gameObject->serialise=false;

    selectedObject= gameObject->AddBehaviour<TextBox>();

    selectedObject->depth=55;

    selectedObject->drawLayer= DrawMode::UI;

    selectedObject->offsetPos= sf::Vector2f(DISPLAYWIDTH*0.08f,DISPLAYHEIGHT*0.08f);

    selectedObject->fontSize=40;

    selectedObject->text="No Selection";

    selectedObject->SetColour(sf::Color::White);



}

void SimpleMapEditor::SelectTerrainObject(SceneObject *prefab)
{
    selectedObject->text=prefab->objectname;
    selectedPrefab=prefab;
}

void SimpleMapEditor::CreateBlock()
{
    currentContext = (new GameObject("TerrainBlock"))->AddBehaviour<RectangleBlock>();

    spawnPos=EngineInputSystem::WorldSpaceMousePos();

    currentContext->gameObject->transform.SetPosition(spawnPos);

}


void SimpleMapEditor::CheckStates()
{

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

    tryCreate=false;

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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Delete))
    {
        DeleteObject();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
    {
        tryCreate=true;
    }

}

void SimpleMapEditor::DeleteObject()
{
    sf::Vector2i pos(posX*tileSize, posY*tileSize);

    auto it = tileMap.find(pos);

    if (it != tileMap.end()) {
        // Position is taken, delete object
        SceneManagement::Destroy(it->second);
        tileMap.erase(it);

    }
}

void SimpleMapEditor::ManageCreation()
{
    if (!tryCreate)
    {
        return;
    }

    if (selectedPrefab==nullptr)
    {
        return;
    }

    sf::Vector2i pos(posX*tileSize, posY*tileSize);

    auto it = tileMap.find(pos);

    if (it == tileMap.end()) {
        // Position is empty, create a new object
        if (selectedPrefab != nullptr) {

            tileMap[pos] = &selectedPrefab->CreateObject(sf::Vector2i(tileSize * posX * snapSize[currentSnap], tileSize * posY * snapSize[currentSnap]));
        }
    }
    else //position is full, create nothing
    {

    }


}

void SimpleMapEditor::ManageSelection()
{

}

void SimpleMapEditor::Update(float deltaTime)
{
    //CheckStates();
    ManageInput();
    CheckStates();
    ManageCreation();
    ManageSaving();
    sf::Vector2f newPos= sf::Vector2f(tileSize*posX*snapSize[currentSnap],tileSize*posY*snapSize[currentSnap]);
    camera->SetCameraPos(newPos);
    selection->transform.SetPosition(newPos);
}

