//
// Created by Tiern on 25/06/2025.
//

//Engine
#include "ObjectSpawnList.h"
#include "../../engine/include/Objects/GameObject.h"
#include "BoxRenderer.h"
#include "Constants.h"
#include "Engine.h"

//Game
#include "SceneCamera.h"
#include "GameManager.h"
#include <UI/GameSpeedUI.h>
#include <UI/ScreenspaceButton.h>

ObjectSpawnList::ObjectSpawnList()
{

}

void EPICPRINTING()
{
    std::cout << "WE HAVE BEEN PRESSED" << std::endl;
}


void ObjectSpawnList::Execute()
{
     GameObject* temp= new GameObject("Our First Button");



     //Generate Camera
     GameObject *cameraTemp= new GameObject("CameraTest");

     SceneCamera* camera = cameraTemp->AddBehaviour<SceneCamera>();

     camera->minBounds = sf::Vector2f(0, 0);
     camera->maxBounds = sf::Vector2f(DISPLAYWIDTH*1.1f, DISPLAYHEIGHT*1.1f);
     camera->minBounds = sf::Vector2f(0, 0);


     camera->renderTarget = &Engine::GEngine->GetRenderWindow();

     camera->cameraView = camera->renderTarget->getView();

     GameObject* manager = new GameObject("Game Manager");

     GameManager* managerBehaviour= manager->AddBehaviour<GameManager>();


     //Spawn UI
    GameObject* timelineUI= new GameObject("TimelineUI");

    GameSpeedUI* gameUI=timelineUI->AddBehaviour<GameSpeedUI>();

    gameUI->Init(managerBehaviour);






}
