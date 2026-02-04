#include "SceneCamera.h"
#include "Engine.h"
#include "EngineInputSystem.h"
#include "math.h"
#include <iostream>
REGISTER_BEHAVIOUR(SceneCamera)
SceneCamera::SceneCamera()
{
	zoomSpeed = 1.1f;
	cameraSpeed = 1000;
	zoomLevel = 1;
}

//Manage Keyboard and mouse input for moving the camera around the screen
void SceneCamera::ManageCamera(float deltaTime)
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


	//Map Movemement
	sf::Vector2f movementVector = sf::Vector2f();
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		movementVector.y -= 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		movementVector.y += 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		movementVector.x -= 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		movementVector.x += 1;
	}

	position = cameraView.getCenter()+movementVector * cameraSpeed * deltaTime;

	position.x = std::clamp(position.x, minBounds.x ,maxBounds.x);

	position.y = std::clamp(position.y, minBounds.y ,maxBounds.y);

	

	cameraView.setCenter(position);
	//cameraView.setSize(cameraSize);
	cameraView.zoom(zoomFactor);

	renderTarget->setView(cameraView);
	
}


void SceneCamera::Update(float deltaTime)
{
	ManageCamera(deltaTime);
}

void SceneCamera::PrintTest()
{
    std::cout << position.x << " jepic " << position.y << std::endl;
}

