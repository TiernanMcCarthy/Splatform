#pragma once

#include <RenderObject.h>

#include <string>
#include <vector>

class TextBox : public  RenderObject
{
public:
    std::string text;

    void Update(float deltaTime) override;
    void Start() override;
    void Render(sf::RenderWindow *target) override;

    void SetColour(sf::Color colour);
	 
    TextBox();
    ~TextBox() = default;

    sf::Vector2<float> offsetPos;

    unsigned int fontSize;
private:

    sf::Text* textBox;

};

