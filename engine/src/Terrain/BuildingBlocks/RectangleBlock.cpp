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
    // Search the parent GameObject for the renderer sibling
    renderer = gameObject->GetBehaviour<BoxRenderer>();
    collider = gameObject->GetBehaviour<AABB>();

    if (renderer == nullptr)
    {
        renderer= gameObject->AddBehaviour<BoxRenderer>();
    }
    if (collider == nullptr)
    {
        collider = gameObject->AddBehaviour<AABB>();
    }
    renderer->depth=1;
}

void RectangleBlock::Update(float deltaTime)
{

}


void RectangleBlock::Start()
{

}




