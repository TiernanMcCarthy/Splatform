#pragma once
#include <Objects/Behaviour.h>
#include <SFML/Graphics.hpp>

namespace DrawMode
{
	//Enum for managing basic draw Layers 
	enum DrawMode
	{
		GAME,
		UI
	};
}
class RenderObject : public Behaviour
{
public:
	DrawMode::DrawMode drawLayer = DrawMode::GAME;

	//Used to calculate Draw Depth (Only useful for SFML, rework for OpenGL or something
	unsigned int depth = 0;

	sf::Vector2<float> dimensions;

	//Render Update for All Render Objects, override for custom behaviours
	virtual void Render(sf::RenderWindow *target);

	virtual void UpdateVisualComponents();

	void Start() override;

	void OnDestroy() override;

	void SetDimensions(float x, float y);
};