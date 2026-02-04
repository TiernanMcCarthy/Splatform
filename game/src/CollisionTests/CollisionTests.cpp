//
// Created by tiernan on 12/25/25.
//
#include "CollisionTests/CollisionTests.h"

#include "../../include/CollisionTests/ColliderDebug.h"
#include "AABB.h"
#include "BoxRenderer.h"
#include "Constants.h"
#include "Objects/GameObject.h"
#include "SceneCamera.h"
#include "SceneLoadDummy.h"

CollisionTests::CollisionTests() {

}

void CollisionTests::Execute()
{


    GameObject* testAABB=new GameObject("TestDebug");
    testAABB->AddBehaviour<ColliderDebug>();
    /*
    //Generate Camera
    GameObject *cameraTemp= new GameObject("CameraTest");

    SceneCamera* camera = cameraTemp->AddBehaviour<SceneCamera>();

    camera->minBounds = sf::Vector2f(0, 0);
    camera->maxBounds = sf::Vector2f(DISPLAYWIDTH*1.1f, DISPLAYHEIGHT*1.1f);
    camera->minBounds = sf::Vector2f(0, 0);


    camera->renderTarget = &Engine::GEngine->GetRenderWindow();

    camera->cameraView = camera->renderTarget->getView();*/



}
