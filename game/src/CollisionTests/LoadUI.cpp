//
// Created by Tiern on 18/02/2026.
//



#include "CollisionTests/LoadUI.h"

#include <TestPlayer/PlayerScenario.h>

#include "UI/Button.h"
REGISTER_BEHAVIOUR(LoadUI);


#include "Objects/GameObject.h"
#include "RenderObject.h"
#include "UI/ScreenspaceButton.h"
#include "UI/TextBox.h"

void LoadUI::Start()
{
    gameObject->transform.SetPosition(DISPLAYWIDTH/2, DISPLAYHEIGHT/2);


    loadSave=(new GameObject("load"))->AddBehaviour<ScreenSpaceButton>();

    loadSave->gameObject->transform.SetPosition(DISPLAYWIDTH/2, DISPLAYHEIGHT/2);



    speedTitle= gameObject->AddBehaviour<TextBox>();

    speedTitle->SetColour(sf::Color::Blue);

    speedTitle->drawLayer = DrawMode::UI;

    speedTitle->text= "Load";

    speedTitle->fontSize=24;
    speedTitle->depth=5;

    speedTitle->offsetPos=sf::Vector2f(-30, -15);
    loadSave->attachedButton->OnPress.Subscribe([]() {
    SceneManagement::LoadScene("MyBeautifulTest");
});

    //loadSave->attachedButton->OnPress.Subscribe([]() {PlayerScenario::Execute();});

}