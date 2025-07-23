//
// Created by Tiern on 25/06/2025.
//

//Engine
#include "ObjectSpawnList.h"
#include "GameObject.h"
#include "Constants.h"
#include "Engine.h"
#include "BoxRenderer.h"

//Game
#include "SceneCamera.h"
#include "TestScript.h"
#include "GameManager.h"

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

     TestScript* testButton = temp->AddBehaviour<TestScript>();


     //Generate Camera
     GameObject *cameraTemp= new GameObject("CameraTest");

     SceneCamera* camera = cameraTemp->AddBehaviour<SceneCamera>();

     camera->minBounds = sf::Vector2f(0, 0);

     camera->maxBounds = sf::Vector2f(DISPLAYWIDTH*1.1f, DISPLAYHEIGHT*1.1f);
     camera->minBounds = sf::Vector2f(0, 0);


     camera->renderTarget = &Engine::GEngine->GetRenderWindow();

     camera->cameraView = camera->renderTarget->getView();

     GameObject* manager = new GameObject("Game Manager");

     manager->AddBehaviour<GameManager>();
}
