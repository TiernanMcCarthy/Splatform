#pragma once
#include "Objects/Behaviour.h"

class Bounds
{
	private:
	//center of collider relative to parent world space position
	sf::Vector2<float> center;

	//Always Half the size of the bounds
	sf::Vector2<float> extents;

public:

	void SetCenter(sf::Vector2<float> cent)
	{
		center = cent;
	}
	
	void ApplyExtents(sf::Vector2<float> extent)
	{
		extents = extent;
	}
};

class Collider : public Behaviour
{

	


};