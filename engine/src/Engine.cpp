#include "Engine.h"
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Constants.h"


#include "RenderObject.h"
#include "BoxRenderer.h"
#include "AABBCollider.h"
#include "EngineInputSystem.h"

Engine* Engine::GEngine = nullptr;

Engine::Engine(bool startEngine)
{
    /* initialize random seed: */
    srand (time(NULL));
    Engine::GEngine = this;
    gameObjects = std::vector<GameObject*>();

    //Create Game Window
    renderWindow = sf::RenderWindow(sf::VideoMode({ DISPLAYWIDTH, DISPLAYHEIGHT }), WINDOW_NAME,sf::State::Windowed);

    //Create Input System
    engineInput = new EngineInputSystem();


    if (startEngine)
    {
        Start();
    }
}

void Engine::Start()
{
    isRunning = true;
    EngineLoop();
}


void Engine::EngineLoop()
{
    if (!isRunning)
    {
        return;
    }

    //Clock for calculating Delta Time
    sf::Clock clock;

    //Create Background
    BoxRenderer* background = (new GameObject("Background"))->AddBehaviour<BoxRenderer>();

    //Setup Background
    float pixelCount = (DISPLAYWIDTH * DISPLAYHEIGHT)/1.5f;

    float pixelRatio = (pixelCount / (256 * 224));

    background->gameObject->transform.localScale = sf::Vector2f(256*pixelRatio, 224*pixelRatio);

    background->gameObject->transform.SetPosition(DISPLAYWIDTH / 2, DISPLAYHEIGHT / 2);

    background->ApplyImage("assets/flatImage.png");


    //Manage Window Settings
    renderWindow.setFramerateLimit(60);
    //Create UI View layer
    sf::View UILayer = renderWindow.getView();
    //Create Game View Layer
    sf::View GameLayer= renderWindow.getView();


    //Manage Startup Sequences, used for spawning objects, scene loading and scene management could
    //Come next
    for (int i=0; i<startupList.size(); i++)
    {
        startupList[i]->Execute();
    }

    //Main Game Loop
    while (renderWindow.isOpen())
    {
        //clean last frame's inputs
        engineInput->CleanInputs();

        //Handle Events
        while (const std::optional event = renderWindow.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                renderWindow.close();
                break;
            }
            else if (const auto* scrollWheel = event->getIf<sf::Event::MouseWheelScrolled>()) //crap and needs to be improved
            {
                engineInput->scrollWheelDelta = scrollWheel->delta;
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                EngineInputSystem::InputSystem->AddInputEvent(*keyPressed);
            }
            else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
            {
                EngineInputSystem::InputSystem->AddInputEvent(*keyReleased);
            }
            else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                EngineInputSystem::InputSystem->AddInputEvent(*mousePressed);
            }
            else if (const auto* mouseReleased = event->getIf<sf::Event::MouseButtonReleased>())
            {
                EngineInputSystem::InputSystem->AddInputEvent(*mouseReleased);
                //EngineInputSystem::InputSystem->AddInputEvent(*mouseReleased);
            }



        }

        //Poll InputSystem
        engineInput->PollInputs();

        sf::Vector2i mousePos = sf::Mouse::getPosition(renderWindow);

        sf::Vector2f worldPos = renderWindow.mapPixelToCoords(mousePos);

        //Get Delta Time
        deltaTime = clock.restart().asSeconds();

        for (int i = 0; i < gameObjects.size(); i++)
        {
            //Update all GameObjects
            gameObjects[i]->Update(deltaTime);
        }


        //Clear Screen and Draw New Scene
        renderWindow.clear();


        //Order Draw Stack for correct Render Order
        SortDrawStack();
        GameLayer=renderWindow.getView();
        for (int i = 0; i < drawStack.size(); i++)
        {
            if (drawStack[i]->drawLayer==DrawMode::GAME)
            {
                renderWindow.setView(GameLayer);
            }
            else
            {
                renderWindow.setView(UILayer);
            }


            drawStack[i]->Render(&renderWindow);
        }
        renderWindow.setView(GameLayer);
        
        renderWindow.display();

        //Clear Destruction Stack for Deleted Objects
        ClearDestructionStack();
    }

    std::cout << "Closing Engine \n" << std::endl;
}

void Engine::ClearDestructionStack()
{
    Object* targetPointer;
    for (int i = 0; i < destructionStack.size(); i++)
    {
        targetPointer = destructionStack[i];
        targetPointer->OnDestroy();
        delete targetPointer;
    }
    destructionStack.clear();
}

/// <summary>
/// Sorts Draw Stack to draw objects by depth priority
/// </summary>
void Engine::SortDrawStack()
{
    if (drawStack.size() > 1)
    {
        std::sort(drawStack.begin(), drawStack.end(), [](RenderObject* a, RenderObject* b)
            {
                float aDepth=a->depth;
                float bDepth=b->depth;

                if (a->drawLayer==DrawMode::UI) {aDepth*=10;}
                if (b->drawLayer==DrawMode::UI) {bDepth*=10;}

                return aDepth < bDepth;
            });
    }
}

void Engine::RemoveObjectFromList(GameObject* g)
{
    if (g)
    {
        gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), g), gameObjects.end());
    }
}

void Engine::RegisterDrawObject(RenderObject* object)
{
    if (object)
    {
        drawStack.push_back(object);
    }
}

void Engine::RemoveDrawObject(RenderObject* object)
{
    if (object)
    {
        drawStack.erase(std::remove(drawStack.begin(), drawStack.end(), object), drawStack.end());
    }
}


void Engine::AddGameObject(GameObject* newObject)
{
    gameObjects.push_back(newObject);
    gameObjects[gameObjects.size() - 1]->Start();
}

void Engine::Destroy(Object *target)
{
    //Destroy target if it's not a null pointer
    if (target)
    {
        destructionStack.push_back(target);
    }
}

float Engine::DeltaTime()
{
    return deltaTime;
}

void Engine::AddStartupSequence(StartupSequence *param)
{
    startupList.push_back(param);
}

sf::RenderWindow &Engine::GetRenderWindow()
{
    return renderWindow;
}



