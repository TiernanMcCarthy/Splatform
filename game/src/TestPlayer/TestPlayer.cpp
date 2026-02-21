//
// Created by Tiern on 18/02/2026.
//

#include "TestPlayer/TestPlayer.h"

REGISTER_BEHAVIOUR(TestPlayer)

#include "Scenes/SceneManager.h"
#include "Terrain/BuildingBlocks/RectangleBlock.h"


void TestPlayer::Start()
{
   blocks=SceneManagement::GetBehavioursOfType<RectangleBlock>();
   
}

void TestPlayer::Update(float deltaTime)
{



}
