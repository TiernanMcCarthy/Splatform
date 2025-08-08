//
// Created by Admin on 08/08/2025.
//

#ifndef GAMESPEEDUI_H
#define GAMESPEEDUI_H
#include "Objects/Behaviour.h"
#endif //GAMESPEEDUI_H

class TextBox;
class ScreenSpaceButton;
class GameManager;

class GameSpeedUI: public Behaviour
{
public:

    void Update(float deltaTime) override;

    void Start() override;

    void Init(GameManager* manager);


private:

    GameManager* manager =nullptr;

    ScreenSpaceButton* slowDown=nullptr;

    ScreenSpaceButton* speedUp =nullptr;

    TextBox* gameSpeed=nullptr;

    TextBox* speedTitle=nullptr;

};