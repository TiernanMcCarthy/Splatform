#pragma once
#include "../../engine/include/Objects/Behaviour.h"
#include <SFML/Graphics.hpp>

class SceneCamera : public Behaviour
{

public:

	float cameraSpeed;

	sf::View cameraView;

	sf::RenderWindow *renderTarget;

	sf::Vector2f size;

	sf::Vector2f position;

	sf::Vector2f minBounds;

	sf::Vector2f maxBounds;

	void Update(float deltaTime) override;

	SceneCamera();

    void PrintTest();
private:
	float zoomLevel;
	float zoomSpeed;
	float oldZoom;
	void ManageCamera(float deltaTime);
};