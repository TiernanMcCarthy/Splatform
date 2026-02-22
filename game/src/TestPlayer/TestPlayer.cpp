//
// Created by Tiern on 18/02/2026.
//

#include "TestPlayer/TestPlayer.h"

#include <Objects/GameObject.h>

#include "BoxRenderer.h"

REGISTER_BEHAVIOUR(TestPlayer)

#include "Collider.h"
#include "AABB.h"
#include "Scenes/SceneManager.h"
#include "Terrain/BuildingBlocks/RectangleBlock.h"
#include "TestPlayer/PlayerSpawn.h"

void TestPlayer::Start()
{
   blocks=SceneManagement::GetBehavioursOfType<RectangleBlock>();

   renderer= gameObject->AddBehaviour<BoxRenderer>();

   renderer->ApplyImage("assets/Egg.png");

   collider=gameObject->AddBehaviour<AABB>();

    //the player should always display above everyone else
   renderer->depth=50;

   gameObject->transform.localScale= sf::Vector2f(100,100);

   PlayerSpawn* spawn = SceneManagement::GetBehaviourOfType<PlayerSpawn>();

   if(spawn)
   {
       gameObject->transform.SetPosition(spawn->gameObject->transform.GetPosition());
   }


}


void TestPlayer::TestCollision()
{
    HitResult result;
    for(int i=0; i<blocks.size(); i++)
    {
        result = collider->IntersectAABB(blocks[i]->collider);
        if (result.debugHit)
        {
            sf::Vector2f newPos=gameObject->transform.GetPosition() + result.delta;

            gameObject->transform.SetPosition(newPos);
        }

    }
}

void TestPlayer::Update(float deltaTime)
{

   float x=0;
   float y=0;



   y+=moveSpeed;
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
   {
     // y-=moveSpeed*deltaTime;
   }
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
   {
      y+=moveSpeed;
   }

   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
   {
      x-=moveSpeed;
   }
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
   {
      x+=moveSpeed;
   }

   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
   {
      y-=300;
   }



   gameObject->transform.SetPosition(gameObject->transform.GetPosition()+sf::Vector2f(x,y)*deltaTime);

   TestCollision();


}
