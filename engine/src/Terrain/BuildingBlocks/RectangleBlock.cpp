//
// Created by Tiern on 19/02/2026.
//
#include "Terrain/BuildingBlocks/RectangleBlock.h"

#include "AABB.h"
#include "BoxRenderer.h"
#include "Objects/GameObject.h"

REGISTER_BEHAVIOUR(RectangleBlock)

void RectangleBlock::Awake()
{
    gameObject->AddBehaviour<AABB>();
    renderer=gameObject->AddBehaviour<BoxRenderer>();
}

void RectangleBlock::Update(float deltaTime)
{

}


void RectangleBlock::Start()
{

}




