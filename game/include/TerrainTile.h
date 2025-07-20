//
// Created by tiernan on 7/9/25.
//
#pragma once
#include "SFML/Graphics/Color.hpp"

//A Settlement can own a tile, they can also reproduce and claim other tiles
class Settlement;

/// Terrain Tiles are a representation of a pixel of the world map. They should be painted and contain reference to who
/// owns them
class TerrainTile
{
public:

    TerrainTile(bool isLand, sf::Color colour);

    void SetOwner(Settlement* newOwner);

    void ClearSettlement();

    Settlement& GetOwner();

    bool IsLand();

    bool IsSettled();

private:

    bool isLand;

    //Manages whether a tile needs to be drawn again
    bool isDirty=false;

    sf::Color originalColour;

    Settlement* owner;
};
