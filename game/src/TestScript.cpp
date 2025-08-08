#include "TestScript.h"
#include "../../engine/include/Objects/GameObject.h"
#include "BoxRenderer.h"
#include "Constants.h"
#include <SFML/System/Clock.hpp>
#include <iostream>
#include <math.h>

static sf::Clock globalClock;

 TestScript::TestScript()
{

}


void TestScript::Start()
{
    gameObject->transform.localScale=sf::Vector2<float>(DISPLAYWIDTH/10, DISPLAYWIDTH/10);

    gameObject->transform.SetPosition(sf::Vector2f(DISPLAYWIDTH/18, DISPLAYHEIGHT/10));

     boxR = gameObject->AddBehaviour<BoxRenderer>();
     //boxR->SetDimensions(gameObject->transform.localScale.x, gameObject->transform.localScale.y);
     activeColour=sf::Color::Green;
     inactiveColour=sf::Color::Red;
     boxR->color = inactiveColour;

     boxR->UpdateVisualComponents();
     boxR->drawLayer=DrawMode::UI;


     //boxR->

    attachedButton=gameObject->AddBehaviour<Button>();
     attachedButton->OnPress.Subscribe(std::bind(&TestScript::ToggleAttached,this));
    attachedButton->worldSpace=false;

     textBox=gameObject->AddBehaviour<TextBox>();
     textBox->text="Our Test Button";
     textBox->depth=2;
     textBox->drawLayer=DrawMode::UI;
     textBox->offsetPos=sf::Vector2<float>(-80,0);
     textBox->fontSize=20;

}
void TestScript::ToggleAttached()
{
    state=!state;

    if (state)
    {
        boxR->color=activeColour;
        boxR->UpdateVisualComponents();
    }
    else
    {
        boxR->color=inactiveColour;
        boxR->UpdateVisualComponents();
    }
}

void TestScript::Update(float deltaTime)  
{  

}
