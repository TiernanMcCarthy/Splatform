#pragma once
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"
#include "Systems/FunctionSubscriber.h"
#include <vector>
#include <time.h>



///Generic Base Input container for most actions,
class GenericInputContainer
{
public:
    virtual ~GenericInputContainer() = default;

    //GenericInputContainer() = default;

    GenericInputContainer()
    {
        wasFirstPerformedThisFrame=false;
        wasReleasedThisFrame=false;
        isPerformed=false;
        wasPerformedLastFrame=false;
        isHeld=false;
        pressTime= 0;
    }

    bool wasFirstPerformedThisFrame{};
    bool wasReleasedThisFrame{};

    bool isPerformed{};

    bool isHeld{};

    long pressTime;



    virtual void Clean()
    {
        wasFirstPerformedThisFrame = false;
        wasReleasedThisFrame = false;
        isPerformed = false;
        isHeld=false;
        pressTime=0;
    }

    void SetPerformed(bool isHappening)
    {
        isPerformed = isHappening;
    }

    virtual void ProcessInput()
    {
        //Find out if the action has happened this frame, good for checking inputs on a frame basis
        if (isPerformed)
        {

            if (!wasPerformedLastFrame)
            {
                wasFirstPerformedThisFrame=true;
                pressTime=time(nullptr);
            }
            else
            {
                wasFirstPerformedThisFrame=false;
                isHeld=true;
            }

            //Record that this action was pressed this frame
            wasPerformedLastFrame=true;
            wasReleasedThisFrame=false;
        }
        else //Records states around the action not happening
        {
            wasReleasedThisFrame=false;
            if (wasPerformedLastFrame==true)
            {
                wasReleasedThisFrame=true;
                pressTime=0;
            }
            else
            {
                wasFirstPerformedThisFrame=false;
            }
            wasPerformedLastFrame=false;
            wasFirstPerformedThisFrame=false;
            isHeld=false;
            pressTime=0;
        }
    }

private:
    bool wasPerformedLastFrame{};
};

///
class FloatInputContainer
{
public:

    float value;

};


class EngineInputSystem
{
public:
	static EngineInputSystem* InputSystem;

	float scrollWheelDelta;

	void PollInputs();

	void CleanInputs();

    void AddInputEvent(sf::Event);


	EngineInputSystem();

#pragma region  Input Sources

    GenericInputContainer *MouseOne;

    GenericInputContainer *MouseTwo;

    GenericInputContainer *eKey;

    GenericInputContainer *pKey;

    GenericInputContainer *upKey;

    GenericInputContainer *downKey;

    GenericInputContainer *leftKey;

    GenericInputContainer *rightKey;

    GenericInputContainer *plus;

    GenericInputContainer *minus;


#pragma endregion

    static sf::Vector2<float> WorldSpaceMousePos();


private:

    //List of Input Events to be processed later, cleaned once per frame;
    std::vector<sf::Event> inputEvents;

    FunctionSubscriber *ProcessInputEvent;

    void BindInputProcessing(GenericInputContainer *objectPointer);
};
