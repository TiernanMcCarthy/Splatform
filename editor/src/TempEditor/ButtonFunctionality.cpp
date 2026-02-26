//
// Created by tiernan on 2/25/26.
//
#include "TempEditor/ButtonFunctionality.h"

#include "TempEditor/EditorButton.h"
#include "TempEditor/SimpleMapEditor.h"

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

    canvas->gameObject->transform.SetPosition(DISPLAYWIDTH/2,DISPLAYHEIGHT*0.95f);

    //deleteButton

    deleteObject= (new GameObject("DeleteButton"))->AddBehaviour<EditorButton>();

    deleteObject->Setup(sf::Color::Red,"Delete",sf::Vector2f(80,80),sf::Vector2f(DISPLAYWIDTH/2,DISPLAYHEIGHT*0.94f));

    deleteObject->button->OnPress.Subscribe(std::bind(&SimpleMapEditor::DeleteObject,SimpleMapEditor::instance));

    deleteObject->text->offsetPos=sf::Vector2f(-35,-15);


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

    terrainText->offsetPos= sf::Vector2f(-45,-DISPLAYHEIGHT*0.45f);

    terrainText->text="Prefabs";

    terrainText->fontSize=24;

    terrainText->depth=50;
}
