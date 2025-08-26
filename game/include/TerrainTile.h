//
// Created by tiernan on 7/9/25.
//
#pragma once
#include "SFML/Graphics/Color.hpp"
#include "SFML/System/Vector2.hpp"

// A Settlement can own a tile, they can also reproduce and claim other tiles
class Settlement;

class WorldMap;

/// Terrain Tiles are a representation of a pixel of the world map. They should be painted and contain reference to who
/// owns them
class TerrainTile
{
public:

    TerrainTile(bool isLand, sf::Color colour,WorldMap* worldObject, int index);

    void SetOwner(Settlement* newOwner);

    void ClearSettlement();

    Settlement& GetOwner();

    void DrawTile(sf::Color colour);

    void ResetTile();



    //Getters


    bool IsLand();

    bool IsSettled();

    sf::Color GetColour();

    sf::Vector2u GetPosition();

    sf::Color GetOriginalColour()
    {
        return originalColour;
    }

    TerrainTile& GetLand(sf::Vector2u pos);

private:

    bool isLand;


    sf::Color originalColour;

    sf::Color currentColour;

    Settlement* owner;

    WorldMap* world;

    int index;

    sf::Vector2u position;
};
