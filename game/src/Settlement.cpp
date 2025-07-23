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



void Settlement::Reproduce(SettlerManager* manager)
{
    sf::Vector2u settlementPos= home->GetPosition();
    Settlement* newSettlement;

    //Above
    TerrainTile* testTile= &home->GetLand(settlementPos- sf::Vector2u(0,-1));
    if (CanSettleThisTile(testTile))
    {
        newSettlement = new Settlement(testTile,team);
        manager->PushSettler(newSettlement);
        reproductionValue=0;
        return;
    }
    //Below
    testTile= &home->GetLand(settlementPos- sf::Vector2u(0,1));
    if (CanSettleThisTile(testTile))
    {
        newSettlement = new Settlement(testTile,team);
        manager->PushSettler(newSettlement);
        reproductionValue=0;
        return;
    }

    //Left
    testTile= &home->GetLand(settlementPos- sf::Vector2u(-1,0));
    if (CanSettleThisTile(testTile))
    {
        newSettlement = new Settlement(testTile,team);
        manager->PushSettler(newSettlement);
        reproductionValue=0;
        return;
    }
    //Right
    testTile= &home->GetLand(settlementPos- sf::Vector2u(1,0));
    if (CanSettleThisTile(testTile))
    {
        newSettlement = new Settlement(testTile,team);
        manager->PushSettler(newSettlement);
        reproductionValue=0;
        return;
    }



    reproductionValue=0;
}


void Settlement::ManageReproduction(SettlerManager* manager)
{
    reproductionValue+=team->GetReproductionRate();

    if (reproductionValue>1.1f)
    {
        Reproduce(manager);
    }
}


void Settlement::Simulate(SettlerManager* manager)
{
    ManageReproduction(manager);

}

