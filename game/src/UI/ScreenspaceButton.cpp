//
// Created by Admin on 08/08/2025.
//

#include <UI/ScreenspaceButton.h>
//Engine
#include "Objects/GameObject.h"
#include <UI/Button.h>
#include <UI/TextBox.h>
#include <BoxRenderer.h>

//Game



ScreenSpaceButton::ScreenSpaceButton()
{

}

void ScreenSpaceButton::Awake()
{
    //Setup Basic Dimensions
    gameObject->transform.localScale= sf::Vector2f(100,100);
    //Create Visual Elements
    attachedButton=gameObject->AddBehaviour<Button>();
    attachedButton->worldSpace=false;

    //Background Renderer
    boxR= gameObject->AddBehaviour<BoxRenderer>();
    boxR->drawLayer=DrawMode::UI;

    //Optional Text box
    textBox=gameObject->AddBehaviour<TextBox>();
    textBox->text="";
    textBox->drawLayer=DrawMode::UI;
    textBox->depth=2;
}


void ScreenSpaceButton::Start()
{

}

void ScreenSpaceButton::Update(float deltaTime)
{

}


void ScreenSpaceButton::SetColour(const sf::Color colour) const
{
    boxR->color = std::move(colour);
}

void ScreenSpaceButton::ApplyImage(const std::string &imagePath) const
{
    boxR->ApplyImage(imagePath);
    boxR->UpdateVisualComponents();
}



void ScreenSpaceButton::UpdateText(const std::string text)
{
    textBox->text=text;
    textBox->UpdateVisualComponents();
}





