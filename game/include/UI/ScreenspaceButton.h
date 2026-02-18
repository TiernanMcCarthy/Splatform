//
// Created by Admin on 08/08/2025.
//

#ifndef SCREENSPACEBUTTON_H
#define SCREENSPACEBUTTON_H
#include <Objects/Behaviour.h>


#endif // SCREENSPACEBUTTON_H

class BoxRenderer;
class TextBox;
class Button;


class ScreenSpaceButton : public Behaviour
{

public:

    ScreenSpaceButton();

    void UpdateText(const std::string text);

    void SetColour(const sf::Color colour) const;

    void ApplyImage(const std::string &imagePath) const;

    void Update(float deltaTime) override;

    void Start() override;

    void Awake() override;

    Button* attachedButton=nullptr;


private:


    TextBox* textBox=nullptr;

    BoxRenderer* boxR=nullptr;

};
