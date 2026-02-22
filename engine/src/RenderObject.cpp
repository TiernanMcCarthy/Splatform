#include "RenderObject.h"
#include "../include/Objects/GameObject.h"
#include "Engine.h"

void RenderObject::Render(sf::RenderWindow *target)
{
}
void RenderObject::UpdateVisualComponents()
{
}
void RenderObject::Start()
{
	Engine::GEngine->RegisterDrawObject(this);
	dimensions = gameObject->transform.localScale;
}

void RenderObject::OnDestroy()
{
    Engine::GEngine->RemoveDrawObject(this);
	Behaviour::OnDestroy();
}

void RenderObject::SetDimensions(float x, float y)
{
	dimensions.x = x;
	dimensions.y = y;
	UpdateVisualComponents();
}
