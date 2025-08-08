#pragma once

#include "Objects/Behaviour.h"

// Basic AABB box collider, more advanced collision system isn't needed right now
class AABBCollider : public Behaviour
{
private:


public:

	AABBCollider();


	bool IsPosInside(sf::Vector2<float> position);


	void Start() override;

	void Update(float deltaTime) override;

	sf::Vector2<float> GetMin();

	sf::Vector2<float> GetMax();

};