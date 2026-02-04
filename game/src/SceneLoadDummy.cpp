//
// Created by tiernux on 04/02/2026.
//
#include "SceneLoadDummy.h"

#include "Constants.h"
#include "Engine.h"
#include "SceneCamera.h"
REGISTER_BEHAVIOUR(SceneLoadDummy);
void SceneLoadDummy::Start()
{
    //Generate Camera

    GameObject *cameraTemp= new GameObject("CameraTest");

    SceneCamera* camera = cameraTemp->AddBehaviour<SceneCamera>();

    camera->minBounds = sf::Vector2f(0, 0);
    camera->maxBounds = sf::Vector2f(DISPLAYWIDTH*1.1f, DISPLAYHEIGHT*1.1f);
    camera->minBounds = sf::Vector2f(0, 0);


    camera->renderTarget = &Engine::GEngine->GetRenderWindow();

    camera->cameraView = camera->renderTarget->getView();
}


void SceneLoadDummy::Update(float deltaTime)
{
    if (EngineInputSystem::InputSystem->MouseOne->wasReleasedThisFrame) {
        testValue++;
        // Print the POINTER address of 'this'
        std::cout << "UPDATE | Addr: " << this << " | ID: " << ObjectID << " | Val: " << testValue << std::endl;
    }
}