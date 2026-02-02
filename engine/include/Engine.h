#pragma once
#include "EngineInputSystem.h"
#include "Objects/GameObject.h"
#include "Objects/Object.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window.hpp"
#include "Scenes/SceneManager.h"
#include "StartupSequence.h"
#include "vector"
class RenderObject;

class GameObject;

class StartupSequence;
using BehaviourID = uint64_t;

class Engine
{
public:

	static Engine *GEngine;

	Engine(bool startEngine = false);



	void Start();

	float DeltaTime();

	void RegisterDrawObject(RenderObject* object);

	void RemoveDrawObject(RenderObject* object);

	void AddStartupSequence(StartupSequence *param);

    sf::RenderWindow &GetRenderWindow();

private:




	//Draw stack that contains all Behaviours that are involved in rendering
	std::vector<RenderObject*> drawStack;

    //time since previous frame
	float deltaTime;

    //fixed delta from last physics update to the next
    float fixedDeltaTime;

    //Fixed timestep of the engine, manages how often the fixed update function happens
    float fixedTimestep=0.16f;

	void EngineLoop();

	void SortDrawStack();

	bool isRunning = false;

	std::vector<StartupSequence*> startupList;

    EngineInputSystem* engineInput;

    sf::RenderWindow renderWindow;

    SceneManagement sceneManager;



protected:
};