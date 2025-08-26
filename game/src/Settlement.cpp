//
// Created by tiernan on 7/14/25.
//
#include "Settlement.h"
#include "TerrainTile.h"
#include "WorldMap.h"
#include "SettlerManager.h"

TerrainTile & Settlement::GetHome()
{
    return *home;
}

 Settlement::Settlement(TerrainTile *newHome,Team* newTeam, SettlerManager* parent)
{
    home=newHome;
    team=newTeam;

    settlementManager=parent;

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

void Settlement::Init()
{
    home->SetOwner(this);
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
    Settlement* newSettlement;

    TerrainTile* testTile;

    if (CanSettleThisTile(testTile=&home->GetLand(settlementPos- sf::Vector2u(0,-1)))) //Above
    {
        settlementManager->CreateSettler(testTile,team);
    }
    else if (CanSettleThisTile(testTile=&home->GetLand(settlementPos- sf::Vector2u(0,1)))) //Below
    {
        settlementManager->CreateSettler(testTile,team);
    }
    else if (CanSettleThisTile(testTile=&home->GetLand(settlementPos- sf::Vector2u(-1,0)))) //Left
    {
        settlementManager->CreateSettler(testTile,team);
    }
    else if (CanSettleThisTile(testTile=&home->GetLand(settlementPos- sf::Vector2u(1,0)))) //Right
    {
        settlementManager->CreateSettler(testTile,team);
    }


    reproductionValue=0;
}


void Settlement::ManageReproduction()
{
    reproductionValue+=team->GetReproductionRate();

    if (reproductionValue>1.1f)
    {
        Reproduce();
    }
}

void Settlement::ResetReproduction()
{
    reproductionValue=0;
}


void Settlement::Simulate()
{
    ManageReproduction();

}

