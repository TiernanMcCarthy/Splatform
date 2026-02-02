#include "BoxRenderer.h"
#include "../include/Objects/GameObject.h"
#include <iostream>
bool BoxRenderer::ApplyImage(std::string path)
{

	renderTexture = new sf::Texture();
	if (renderTexture->loadFromFile(path))
	{
		box.setTexture(renderTexture);
	    return true;
		//Texture Loaded
	}
    std::cout << "Invalid path or file type at " + path << std::endl;
    return false;

}


void BoxRenderer::ApplyImage(sf::Image& image)
{
   // if (&image==nullptr)
   // {
   //     std::cout<<"Failed to load image"<<std::endl;
    //    return;
  //  }

    renderTexture= new sf::Texture(image);

    box.setTexture(renderTexture);

}


void BoxRenderer::Render(sf::RenderWindow *target)
{
	if (target)
	{
		UpdateVisualComponents();
	    sf::Vector2<float> pos=gameObject->transform.GetPosition();
	    box.setPosition(gameObject->transform.GetPosition());
	    box.setSize(gameObject->transform.localScale);
		box.setOrigin(sf::Vector2f(gameObject->transform.localScale.x / 2, gameObject->transform.localScale.y / 2));
		target->draw(box);


	}
}

void BoxRenderer::UpdateVisualComponents()
{
	box.setSize(gameObject->transform.localScale);
    box.setOrigin(sf::Vector2f(gameObject->transform.localScale.x / 2, gameObject->transform.localScale.y / 2));
    box.setRotation(sf::degrees(gameObject->transform.localRotation.x));
    if (renderTexture==nullptr)
    {
        box.setFillColor(color);
    }
    else
    {
        box.setTexture(renderTexture);
    }
}


void BoxRenderer::Start()
{
	RenderObject::Start();
	box = sf::RectangleShape(gameObject->transform.localScale);
    box.setOrigin(sf::Vector2f(gameObject->transform.localScale.x / 2, gameObject->transform.localScale.y / 2));
	box.setFillColor(color);
}

BoxRenderer::BoxRenderer(sf::Vector2<float> size)
{
	dimensions = size;
	color = sf::Color::White;
}
