//
// Created by tiernan on 2/25/26.
//
#include "TempEditor/ButtonFunctionality.h"

#include <BoxRenderer.h>
#include <Constants.h>
#include <Objects/GameObject.h>
#include <UI/TextBox.h>


void ButtonFunctionality::Start()
{

    //Create fake canvas
    canvas=(new GameObject("canvas"))->AddBehaviour<BoxRenderer>();

    canvas->gameObject->serialise=false;

    canvas->color= sf::Color(198,198,198);

    canvas->depth=50;

    canvas->drawLayer=DrawMode::UI;

    canvas->gameObject->transform.localScale= sf::Vector2f(DISPLAYWIDTH,DISPLAYHEIGHT*0.1f);

    canvas->gameObject->transform.SetPosition(DISPLAYWIDTH/2,DISPLAYHEIGHT*0.9f);

    deleteObject= (new GameObject("DeleteButton"))->AddBehaviour<Button>();

    deleteObject->gameObject->serialise=false;

    deleteObject->gameObject->AddBehaviour<BoxRenderer>();

    deleteObject->gameObject->GetBehaviour<BoxRenderer>()->drawLayer=DrawMode::UI;

    deleteObject->gameObject->GetBehaviour<BoxRenderer>()->color=sf::Color::Red;

    deleteObject->gameObject->GetBehaviour<BoxRenderer>()->depth=59;

    deleteObject->gameObject->transform.localScale= sf::Vector2f(80,80);

    deleteObject->gameObject->transform.SetPosition(DISPLAYWIDTH/2,DISPLAYHEIGHT*0.89f);

    TextBox* deleteText= deleteObject->gameObject->AddBehaviour<TextBox>();

    deleteText->drawLayer=DrawMode::UI;

    deleteText->offsetPos= sf::Vector2f(-35,-15);
    deleteText->fontSize=22;

    deleteText->depth=60;

    deleteText->text="Delete";

    //Create terrain canvas
    terrainCanvas=(new GameObject("canvas"))->AddBehaviour<BoxRenderer>();

    terrainCanvas->depth=49;

    terrainCanvas->gameObject->serialise=false;

    terrainCanvas->color= sf::Color(71,71,71);

    terrainCanvas->drawLayer=DrawMode::UI;

    terrainCanvas->gameObject->transform.localScale= sf::Vector2f(DISPLAYWIDTH*0.05f,DISPLAYHEIGHT);

    terrainCanvas->gameObject->transform.SetPosition(DISPLAYWIDTH*0.025f,DISPLAYHEIGHT*0.5f);

    TextBox* terrainText= terrainCanvas->gameObject->AddBehaviour<TextBox>();

    terrainText->drawLayer=DrawMode::UI;

    terrainText->offsetPos= sf::Vector2f(-35,-DISPLAYHEIGHT/0.45f);
}
