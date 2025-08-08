#pragma once
#include "../../engine/include/Objects/Behaviour.h"
#include "../../engine/include/UI/Button.h"
#include "../../engine/include/UI/TextBox.h"
#include "BoxRenderer.h"

#include <iostream>

class TestScript : public Behaviour {
public:
    void Start() override;
    void Update(float deltatime) override;

    TestScript();



    bool state=false;

    void ToggleAttached();

    sf::Color activeColour;
    sf::Color inactiveColour;

private:
    Button* attachedButton;

    TextBox* textBox;

    BoxRenderer* boxR;
};
