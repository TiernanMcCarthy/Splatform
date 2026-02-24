#include "EngineInputSystem.h"
#include "Engine.h"
#include <iostream>
EngineInputSystem* EngineInputSystem::InputSystem = nullptr;


void EngineInputSystem::PollInputs()
{
    for (int i = 0; i < inputEvents.size(); i++)
    {

        //Keypresses
        if (const auto* keyPressed = inputEvents[i].getIf<sf::Event::KeyPressed>())
        {

            if (keyPressed->scancode==sf::Keyboard::Scan::Escape)
            {
                std::cout << "Escape pressed" << std::endl;
            }
            else if (keyPressed->scancode==sf::Keyboard::Scan::E)
            {
                eKey->isPerformed = true;
            }
            else if (keyPressed->scancode==sf::Keyboard::Scan::P)
            {
                pKey->isPerformed = true;
            }
            else if (keyPressed->scancode==sf::Keyboard::Scan::Up)
            {
                upKey->isPerformed = true;
            }
            else if (keyPressed->scancode==sf::Keyboard::Scan::Down)
            {
                downKey->isPerformed = true;
            }
            else if (keyPressed->scancode==sf::Keyboard::Scan::Left)
            {
                leftKey->isPerformed = true;
            }
            else if (keyPressed->scancode==sf::Keyboard::Scan::Right)
            {
                rightKey->isPerformed = true;
            }
            else if (keyPressed->scancode==sf::Keyboard::Scan::Equal)
            {
                plus->isPerformed = true;
            }
            else if (keyPressed->scancode==sf::Keyboard::Scan::Hyphen)
            {
                minus->isPerformed = true;
            }
        }
        if(const auto* keyReleased = inputEvents[i].getIf<sf::Event::KeyReleased>())
        {
            if (keyReleased->scancode==sf::Keyboard::Scan::E)
            {
                eKey->isPerformed = false;
            }
            else if (keyReleased->scancode==sf::Keyboard::Scan::P)
            {
                pKey->isPerformed = false;
            }
            else if (keyReleased->scancode==sf::Keyboard::Scan::Up)
            {
                upKey->isPerformed = false;
            }
            else if (keyReleased->scancode==sf::Keyboard::Scan::Down)
            {
                downKey->isPerformed = false;
            }
            else if (keyReleased->scancode==sf::Keyboard::Scan::Left)
            {
                leftKey->isPerformed = false;
            }
            else if (keyReleased->scancode==sf::Keyboard::Scan::Right)
            {
                rightKey->isPerformed = false;
            }
            else if (keyReleased->scancode==sf::Keyboard::Scan::Equal)
            {
                plus->isPerformed = false;
            }
            else if (keyReleased->scancode==sf::Keyboard::Scan::Hyphen)
            {
                minus->isPerformed = false;
            }
        }
        else if (const auto* mousePressed=inputEvents[i].getIf<sf::Event::MouseButtonPressed>())
        {
            if (mousePressed->button==sf::Mouse::Button::Left)
            {
                MouseOne->isPerformed=true;
            }
            if (mousePressed->button==sf::Mouse::Button::Right)
            {
                MouseTwo->isPerformed=true;
            }
        }
        else if (const auto* mouseReleased=inputEvents[i].getIf<sf::Event::MouseButtonReleased>())
        {
            if (mouseReleased->button==sf::Mouse::Button::Left)
            {
                MouseOne->isPerformed=false;
            }
            if (mouseReleased->button==sf::Mouse::Button::Right)
            {
                MouseTwo->isPerformed=false;
            }
        }


    }
    //MouseOne->ProcessInput();
    ProcessInputEvent->Activate();
}

void EngineInputSystem::CleanInputs()
{
    inputEvents.clear();
	scrollWheelDelta = 0;
}

EngineInputSystem::EngineInputSystem()
{
    InputSystem = this;
    scrollWheelDelta = 0;
    inputEvents = std::vector<sf::Event>();
    ProcessInputEvent = new FunctionSubscriber();


    BindInputProcessing(MouseOne = new GenericInputContainer());

    BindInputProcessing(MouseTwo= new GenericInputContainer());

    BindInputProcessing(eKey= new GenericInputContainer());

    BindInputProcessing(pKey= new GenericInputContainer());

    BindInputProcessing(upKey= new GenericInputContainer());

    BindInputProcessing(downKey= new GenericInputContainer());

    BindInputProcessing(rightKey= new GenericInputContainer());

    BindInputProcessing(leftKey= new GenericInputContainer());

    BindInputProcessing(plus= new GenericInputContainer());

    BindInputProcessing(minus= new GenericInputContainer());


}

void EngineInputSystem::BindInputProcessing(GenericInputContainer *objectPointer)
{
    ProcessInputEvent->Subscribe(std::bind(&GenericInputContainer::ProcessInput, objectPointer));
}




void EngineInputSystem::AddInputEvent(sf::Event event)
{
    inputEvents.push_back(event);
}


sf::Vector2<float> EngineInputSystem::WorldSpaceMousePos()
{
    return Engine::GEngine->GetRenderWindow().mapPixelToCoords(sf::Mouse::getPosition(Engine::GEngine->GetRenderWindow()));
}



