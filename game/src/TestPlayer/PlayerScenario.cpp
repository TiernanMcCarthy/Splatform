//
// Created by tiernan on 2/21/26.
//
#include "TestPlayer/PlayerScenario.h"

#include <Objects/GameObject.h>
#include <Scenes/SceneManager.h>

#include "TestPlayer/TestPlayer.h"
#include "TestPlayer/PlayerSpawn.h"

void PlayerScenario::Execute()
{
    PlayerSpawn* spawn=SceneManagement::GetBehaviourOfType<PlayerSpawn>();

    TestPlayer* test = (new GameObject("TestPlayer"))->AddBehaviour<TestPlayer>();

    test->gameObject->transform.SetPosition(spawn->gameObject->transform.GetPosition());




}
