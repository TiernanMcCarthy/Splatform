//
// Created by tiernan on 7/9/25.
//
#pragma once

#include "Behaviour.h"
#include "BoxRenderer.h"

class TerrainTile;


//Simple structure for informing what colours to apply where
struct DrawCommand
{
public:
    sf::Vector2u coords;
    sf::Color colour;

    explicit DrawCommand(sf::Vector2u pos, const sf::Color temp=sf::Color::Yellow)
    {
        coords=pos;
        colour=temp;
    }
};

class WorldMap : public Behaviour {
public:

    WorldMap();
    ~WorldMap()= default;

    void Start() override;
    void Update(float deltatime) override;

    bool LoadMap(std::string path);

    void DrawMap();

    void AddDrawCommand(DrawCommand dc);

    TerrainTile* GetRandomTile();

    TerrainTile* GetTile(int x, int y);

    TerrainTile* GetTile(sf::Vector2u pos);

    sf::Vector2u ConvertIndexToCoordinates(int index);

private:

    sf::Vector2u dimensions;

    BoxRenderer* worldMapVisual;

    sf::Image mapImage;

    std::vector<TerrainTile*> world;

    std::vector<DrawCommand> drawCommands;

    unsigned int populatedTileCount=0;

    unsigned int habitableTileCount=0;

};
