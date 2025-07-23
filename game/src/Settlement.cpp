//
// Created by tiernan on 7/14/25.
//
#include "Settlement.h"
#include "TerrainTile.h"
#include "WorldMap.h"

TerrainTile & Settlement::GetHome()
{
    return *home;
}

 Settlement::Settlement(TerrainTile *newHome,Team* newTeam)
{
    home=newHome;
    team=newTeam;

    //Draw Home Tile as team Colour
    if (home!=nullptr)
    {
        home->DrawTile(team->GetTeamColour());
    }

    reproductionValue=0;
}

 Settlement::~Settlement()
{
    home=nullptr;
}

bool CanSettleThisTile(TerrainTile* testTile)
{
    if (testTile==nullptr)
    {
        return false;
    }

    if (!testTile->IsLand())
    {
        return false;
    }

    if (testTile->IsSettled())
    {
        return false;
    }

    return true;
}

void Settlement::Reproduce()
{
    sf::Vector2u settlementPos= home->GetPosition();

    //Above
    TerrainTile* testTile= &home->GetLand(settlementPos- sf::Vector2u(0,-1));

    if (CanSettleThisTile(testTile))
    {

    }

    reproductionValue=0;
}


void Settlement::ManageReproduction()
{
    reproductionValue+=team->GetReproductionRate();

    if (reproductionValue>100)
    {

    }
}


void Settlement::Simulate()
{
    ManageReproduction();

}

