//
// Created by tiernux on 26/02/2026.
//

#ifndef SPLATFORM_EDITORBUTTON_H
#define SPLATFORM_EDITORBUTTON_H
#include "Objects/GameObject.h"

class TextBox;
class BoxRenderer;
class Button;
class EditorButton : public Behaviour
{
public:

    Button* button;

    BoxRenderer* renderer;

    TextBox* text;

    void Awake() override;

    void Start() override;

    void Setup(sf::Color colour=sf::Color::Red,std::string textString="",sf::Vector2f size=sf::Vector2f(100,100),sf::Vector2f pos= sf::Vector2f(0,0),int fontSize=22);


};

#endif // SPLATFORM_EDITORBUTTON_H
