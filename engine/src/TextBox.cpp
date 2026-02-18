#include <UI/TextBox.h>
#include <Objects/GameObject.h>

#include "FontManager.h"

 TextBox::TextBox()
{

}

void TextBox::SetColour(sf::Color colour)
{
    textBox->setFillColor(colour);
}

void TextBox::Awake()
 {
     RenderObject::Start();
     textBox= new sf::Text(*FontManager::defaultFont);
     textBox->setFillColor(sf::Color::Black);
     offsetPos = sf::Vector2f();
     fontSize=textBox->getCharacterSize();
 }


void TextBox::Start()
{
    // RenderObject::Start();
    //textBox= new sf::Text(*FontManager::defaultFont);
    // textBox->setFillColor(sf::Color::Black);
    // offsetPos = sf::Vector2f();
    // fontSize=textBox->getCharacterSize();
}

void TextBox::Update(float deltaTime)
{
    textBox->setString(text);
    textBox->setPosition(gameObject->transform.localPosition+offsetPos);
     textBox->setCharacterSize(fontSize);
}

void TextBox::Render(sf::RenderWindow *target)
 {
    target->draw(*textBox);
 }