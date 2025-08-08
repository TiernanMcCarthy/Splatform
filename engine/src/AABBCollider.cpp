#include "AABBCollider.h"
#include "../include/Objects/GameObject.h"
#include <iostream>

AABBCollider::AABBCollider()
{

}

bool AABBCollider::IsPosInside(sf::Vector2<float> position)
{
	sf::Vector2<float> min = GetMin();
	sf::Vector2<float> max = GetMax();

	bool result =
		position.x >= min.x &&
		position.x <= max.x &&
		position.y >= min.y &&
		position.y <= max.y;

	return result;
}

void AABBCollider::Start()
{

}

void AABBCollider::Update(float deltaTime)
{
}



sf::Vector2<float> AABBCollider::GetMin()
{
	sf::Vector2<float> min = sf::Vector2<float>(
		gameObject->transform.GetPosition().x - gameObject->transform.localScale.x/2,
		gameObject->transform.GetPosition().y - gameObject->transform.localScale.y/2);
	return min;
}

sf::Vector2<float> AABBCollider::GetMax()
{
	sf::Vector2<float> max = sf::Vector2<float>(
		gameObject->transform.GetPosition().x + gameObject->transform.localScale.x/2,
		gameObject->transform.GetPosition().y + gameObject->transform.localScale.y/2);
	return max;
}
