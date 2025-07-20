//
// Created by tiernan on 7/9/25.
//
#pragma once

#include "Behaviour.h"
#include "BoxRenderer.h"

class TerrainTile;

class WorldMap : public Behaviour {
public:

    WorldMap();
    ~WorldMap()= default;

    void Start() override;
    void Update(float deltatime) override;

    bool LoadMap(std::string path);

    void DrawMap();

    TerrainTile* GetRandomTile();

private:

    BoxRenderer* worldMapVisual;

    sf::Image mapImage;

    std::vector<TerrainTile*> world;

    unsigned int populatedTileCount=0;

    unsigned int habitableTileCount=0;

};
