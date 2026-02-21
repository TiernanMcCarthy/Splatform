//
// Created by Tiern on 18/02/2026.
//

#include "TestPlayer/TestPlayer.h"

#include <Objects/GameObject.h>

#include "BoxRenderer.h"

REGISTER_BEHAVIOUR(TestPlayer)

#include "Scenes/SceneManager.h"
#include "Terrain/BuildingBlocks/RectangleBlock.h"


void TestPlayer::Start()
{
   blocks=SceneManagement::GetBehavioursOfType<RectangleBlock>();

   renderer= gameObject->AddBehaviour<BoxRenderer>();

   renderer->ApplyImage("assets/egg.jpg");

   gameObject->transform.localScale= sf::Vector2f(100,100);

}

void TestPlayer::Update(float deltaTime)
{

   float x=0;
   float y=0;
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
   {
      y-=moveSpeed*deltaTime;
   }
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
   {
      y+=moveSpeed*deltaTime;
   }

   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
   {
      x-=moveSpeed*deltaTime;
   }
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
   {
      x+=moveSpeed*deltaTime;
   }

   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G))
   {
      moveSpeed+=50;
      std::cout<<moveSpeed<<std::endl;
   }

   gameObject->transform.SetPosition(gameObject->transform.GetPosition()+sf::Vector2f(x,y));


}
