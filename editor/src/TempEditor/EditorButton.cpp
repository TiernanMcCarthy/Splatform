//
// Created by tiernux on 26/02/2026.
//
#include "TempEditor/EditorButton.h"

#include <utility>
#include "BoxRenderer.h"
#include "UI/TextBox.h"
#include "UI/Button.h"

void EditorButton::Awake()
{
    renderer= gameObject->AddBehaviour<BoxRenderer>();
    button= gameObject->AddBehaviour<Button>();
    text= gameObject->AddBehaviour<TextBox>();
}

void EditorButton::Start()
{

}

void EditorButton::Setup(sf::Color colour, std::string textString, sf::Vector2f size, sf::Vector2f pos,int fontSize)
{
    gameObject->transform.localScale=size;
    gameObject->transform.SetPosition(pos);

    renderer->color=colour;
    text->text=std::move(textString);

    button->worldSpace=false;

    renderer->drawLayer=DrawMode::UI;

    renderer->depth=59;

    text->depth=60;

    text->drawLayer=DrawMode::UI;

    text->fontSize=fontSize;

    gameObject->serialise=false;

}