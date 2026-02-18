#include <iostream>
#include <SFML/Graphics.hpp>

#include "CollisionTests/LoadSaveTest.h"
#include "Engine.h"
#include "FontManager.h"
#include "ObjectSpawnList.h"
#include "StartupSequence.h"
#include "include/CollisionTests/CollisionTests.h"

int main()
{
    //Initialising Game Engine
    std::cout << "Initialising Game Engine \n" << std::endl;
    Engine gameEngine = Engine();



    //Start FontManager
    sf::Font font;
    std::cout << "Loading Fonts \n" << std::endl;
    if (font.openFromFile("assets/arial.ttf"))
    {
        FontManager::SetDefaultFont(&font);
    }
    else
    {
        std::cout << "FontLoading failed, please ensure there is a font in project folder \n" << std::endl;
        return 1;
    }

    std::cout << "Starting Engine \n" << std::endl;

    ///These are some incredibly temporary start up scripts, will be replaced when the editor has been made
    LoadSaveTEST temp = LoadSaveTEST();
    gameEngine.AddStartupSequence(&temp);

    //CollisionTests temp2 = CollisionTests();
    //gameEngine.AddStartupSequence(&temp2);
    gameEngine.Start();



}

