//
// Created by Tiern on 18/02/2026.
//

#include "TestPlayer/TestPlayer.h"

#include <Objects/GameObject.h>

#include "BoxRenderer.h"
#include "SceneCamera.h"

REGISTER_BEHAVIOUR(TestPlayer)

#include "AABB.h"
#include "Collider.h"
#include "Scenes/SceneManager.h"
#include "Terrain/BuildingBlocks/RectangleBlock.h"
#include "TestPlayer/PlayerSpawn.h"

void TestPlayer::Start()
{
   blocks=SceneManagement::GetBehavioursOfType<RectangleBlock>();

   renderer= gameObject->AddBehaviour<BoxRenderer>();

   renderer->ApplyImage("assets/Egg.png");

   gameObject->transform.localScale= sf::Vector2f(100,100);

   collider=gameObject->AddBehaviour<AABB>();

   collider->transformBasedSize=false;

   collider->SetHalfSize(sf::Vector2f(19,39));

    //the player should always display above everyone else
   renderer->depth=50;



   PlayerSpawn* spawn = SceneManagement::GetBehaviourOfType<PlayerSpawn>();

   if(spawn)
   {
       gameObject->transform.SetPosition(spawn->gameObject->transform.GetPosition());
   }

    if (Engine::GEngine->GetPlayMode()==PlayMode::Game)
    {
        SceneCamera* tempCam= (new GameObject("Blah"))->AddBehaviour<SceneCamera>();
    }



}

void TestPlayer::AddScore(int scoreValue)
{
    score+=scoreValue;
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

       //If we just hit a wall straight on
       if (std::abs(result.normal.x)==1)
       {
          velocity.x=0;
       }

       //if we hit a ceiling dead on
       if (std::abs(result.normal.y)==1)
       {
          velocity.y=0;
       }


    }
}

void TestPlayer::CheckJump(float deltaTime)
{

   isGrounded=false;
   HitResult result;
   for (int i=0; i<blocks.size(); i++)
   {
      result = blocks[i]->collider->IntersectSegment(gameObject->transform.localPosition,sf::Vector2f(0,collider->GetHalfSize().y+2));

      if (result.debugHit)
      {
         isGrounded=true;
         break;
      }
   }
   if (tryJump && isGrounded)
   {
      isGrounded=false;

      velocity.y-=jumpForce*deltaTime;
   }
   if (isGrounded)
   {
      velocity.y=0;
   }

}

void TestPlayer::HandleInput()
{
   horizontalInput=0;
   tryJump=false;

   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
   {
      horizontalInput-=1;
   }
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
   {
      horizontalInput+=1;
   }

   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
   {
      tryJump=true;
   }


}

void TestPlayer::ApplyGravity(float deltaTime)
{
   velocity-= sf::Vector2f(0,gravityForce*deltaTime);
}

enum Direction {
   STATIONARY,
   RIGHT,
   LEFT
};

void TestPlayer::ManageDrag()
{
   velocity.x*=groundDrag;
}

void TestPlayer::ManageMovement(float deltaTime)
{
   Direction dir=STATIONARY;

   //character going too slow, stop them
   if (std::abs(velocity.x)>0.1f) {
      //determine direction
      if (velocity.x>0)
      {
         dir=RIGHT;
      }
      else if (velocity.x<0)
      {
         dir=LEFT;
      }
   }

   //
   float speedRatio= std::abs(velocity.x)/maxSpeed;

   float speedMultiplier= 1.2f-speedRatio;

   float acel=horizontalInput*acceleration*speedMultiplier*deltaTime;

   velocity.x+=acel;

   gameObject->transform.localPosition+=velocity;
}

void TestPlayer::Update(float deltaTime)
{
   HandleInput();
   ApplyGravity(deltaTime);
   CheckJump(deltaTime);
   ManageMovement(deltaTime);
   ManageDrag();
   TestCollision();


}
