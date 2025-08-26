//
// Created by Admin on 08/08/2025.
//
#include <UI/GameSpeedUI.h>

//Engine
#include "Constants.h"
#include <Objects/GameObject.h>
#include <UI/TextBox.h>
#include "UI/Button.h"

// Game

#include "GameManager.h"

#include <UI/ScreenspaceButton.h>


void GameSpeedUI::Init(GameManager *managerG)
{
    manager=managerG;

    speedUp->attachedButton->OnPress.Subscribe(std::bind(&GameManager::IncreaseIterationSpeed,manager));

    slowDown->attachedButton->OnPress.Subscribe(std::bind(&GameManager::DecreaseIterationSpeed,manager));
}


void GameSpeedUI::Start()
{

    //Right
    gameObject->transform.localPosition=sf::Vector2f(DISPLAYWIDTH*0.9f, 100);

    gameObject->transform.localScale= sf::Vector2f(100,100);
    //Spawn Buttons For Game Speed
    GameObject* speedUpButton= new GameObject("Speed Up Button");

    speedUpButton->transform.parent=gameObject->transform.parent;

    //speedUpButton->transform.localPosition=sf::Vector2f(0,0);

    speedUpButton->transform.localPosition=gameObject->transform.localPosition+sf::Vector2f(100, 0);

    speedUpButton->transform.localScale=sf::Vector2f(100,100);

    speedUp=speedUpButton->AddBehaviour<ScreenSpaceButton>();

    //speedUp->attachedButton->OnPress.Subscribe(std::bind(&GameManager::IncreaseIterationSpeed,managerBehaviour));

    speedUp->ApplyImage("assets/ui/Arrow.png");

    //Left
    //Spawn Buttons For Game Speed
    GameObject* slowDownButton= new GameObject("Speed Up Button");

    slowDownButton->transform.parent=gameObject->transform.parent;

    //speedUpButton->transform.localPosition=sf::Vector2f(0,0);

    slowDownButton->transform.localPosition=gameObject->transform.localPosition-sf::Vector2f(100, 0);

    slowDownButton->transform.localRotation= sf::Vector2f(180, 0);

    slowDownButton->transform.localScale=sf::Vector2f(100,100);

    slowDown=slowDownButton->AddBehaviour<ScreenSpaceButton>();

    //speedUp->attachedButton->OnPress.Subscribe(std::bind(&GameManager::IncreaseIterationSpeed,managerBehaviour));

    slowDown->ApplyImage("assets/ui/Arrow.png");



    //Spawn Text Elements

    speedTitle= gameObject->AddBehaviour<TextBox>();

    speedTitle->SetColour(sf::Color::Blue);

    speedTitle->drawLayer=DrawMode::UI;

    speedTitle->text= "Game Speed";

    speedTitle->fontSize=24;

    speedTitle->offsetPos=sf::Vector2f(-70, -60);

    //Value

    gameSpeed= gameObject->AddBehaviour<TextBox>();

    gameSpeed->SetColour(sf::Color::Blue);

    gameSpeed->drawLayer=DrawMode::UI;

    gameSpeed->text="0";

    gameSpeed->fontSize=30;

    gameSpeed->offsetPos=sf::Vector2f(-10, -20);
}


void GameSpeedUI::Update(float deltaTime)
{
    gameSpeed->text=std::to_string(manager->GetGameSpeed());
}

