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


    //Generate Camera
    GameObject *cameraTemp= new GameObject("CameraTest");

    SceneCamera* camera = cameraTemp->AddBehaviour<SceneCamera>();





}
