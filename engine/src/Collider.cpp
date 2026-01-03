//
// Created by tiernux on 27/12/2025.
//
#include "Collider.h"


HitResult::HitResult() {
    hitTime=-1;
    hitPosition=sf::Vector2f();
    col=nullptr;
    debugHit=false;
}


SweepResult::SweepResult()
{
    
}
