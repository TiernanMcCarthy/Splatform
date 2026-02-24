//
// Created by tiernan on 2/24/26.
//
#include "TempEditor/EditorTempCamera.h"

#include <EngineInputSystem.h>
#include <Objects/GameObject.h>

void EditorTempCamera::Start()
{
    renderTarget = &Engine::GEngine->GetRenderWindow();

    cameraView = renderTarget->getView();

}

void EditorTempCamera::SetCameraPos(sf::Vector2f pos)
{
    gameObject->transform.SetPosition(pos);
}


void EditorTempCamera::Update(float deltaTime)
{
    //Camera Zoom
    oldZoom = zoomLevel;
    if (EngineInputSystem::InputSystem->scrollWheelDelta > 0) //Zoom in by reducing zoom factor
    {
        zoomLevel /= zoomSpeed;
    }
    else if (EngineInputSystem::InputSystem->scrollWheelDelta < 0)
    {
        zoomLevel *= zoomSpeed;
    }

    zoomLevel = std::clamp(zoomLevel, 0.05f, 2.5f);

    //Get new zoom by comparing new to old
    float zoomFactor = zoomLevel / oldZoom;

    //cameraView.setSize(cameraSize);
    cameraView.zoom(zoomFactor);

    cameraView.setCenter(gameObject->transform.GetPosition());

    renderTarget->setView(cameraView);
}
