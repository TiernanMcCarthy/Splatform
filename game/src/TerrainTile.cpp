//
// Created by tiernan on 7/13/25.
//

#include "TerrainTile.h"

 TerrainTile::TerrainTile(bool land, sf::Color colour)
{
    isLand=land;
     originalColour=colour;
     owner=nullptr;
}

bool TerrainTile::IsLand()
{
    return isLand;
}

bool TerrainTile::IsSettled()
{
     if (owner!=nullptr)
     {
         return true;
     }

     return false;
 }


void TerrainTile::ClearSettlement()
{
    owner=nullptr;
}

void TerrainTile::SetOwner(Settlement* newOwner)
{
    if (owner!=nullptr)
    {
        owner=newOwner;
    }
}

Settlement& TerrainTile::GetOwner()
{
    return *owner;
}