//
// Created by tiernan on 7/14/25.
//
#include "Settlement.h"
#include "TerrainTile.h"
#include "WorldMap.h"
#include "SettlerManager.h"

#include <algorithm>
#include <random>
sf::Color Team::capitalColour;
std::array<sf::Vector2i, 4> Settlement::directions = {
    sf::Vector2i(0, -1),
    sf::Vector2i(0,  1),
    sf::Vector2i(1,  0),
    sf::Vector2i(-1, 0)
};


TerrainTile & Settlement::GetHome()
{
    return *home;
}

 Settlement::Settlement(TerrainTile *newHome,Team* newTeam, SettlerManager* parent)
{
    home=newHome;
    home->SetOwner(this);
    team=newTeam;

    settlementManager=parent;

    isAlive=false;

    reproductionValue=0;
}

 Settlement::~Settlement()
{
    home=nullptr;
}

void Settlement::Init()
{
    home->SetOwner(this);
    home->DrawTile(team->GetTeamColour());
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

int Settlement::GetTeamID()
{
    return team->GetTeamID();
}


bool Settlement::CanAttackThisTile(TerrainTile* testTile)
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
        if (testTile->GetOwner().GetTeamID()!= team->GetTeamID())
        {
            return true;
        }
    }

    return false;

}



void Settlement::Reproduce()
{
    sf::Vector2u settlementPos= home->GetPosition();
    Settlement* newSettlement;

    TerrainTile* testTile;

    for (int i=0; i<Settlement::directions.size(); i++)
    {
        sf::Vector2u pos= sf::Vector2u(settlementPos.x-directions[i].x, settlementPos.y-directions[i].y);
        if (CanSettleThisTile(testTile=&home->GetLand(pos)))
        {
            settlementManager->CreateSettler(testTile,team);
            break;
        }
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

bool Settlement::IsAlive() const
{
    return isAlive;
}

void Settlement::ResetSettlement()
{

}


void Settlement::MakeActive(Team *newTeam)
{
    team=newTeam;

    isAlive=true;

    health=100;

    team->AddLand();

    ResetReproduction();

    Init();
}

void Settlement::Kill()
{
    isAlive=false;
    health=0;
    home->DrawTile(sf::Color(0,0,0,255));
    team->RemoveLand();
    team=nullptr;
}

void Settlement::ReceiveDamage(float damage)
{
    health=health-damage;

    if (health<=0)
    {
        Kill();
    }
}


void Settlement::Attack(Settlement* target)
{
    target->ReceiveDamage(attack+team->GetlandCount()*0.0006f+team->GetManpowerBonus());
}


void Settlement::AttackState()
{
    sf::Vector2u settlementPos= home->GetPosition();
    //Find a tile to attack;
    TerrainTile* testTile;
    for (int i=0; i<Settlement::directions.size(); i++)
    {
        sf::Vector2u pos= sf::Vector2u(settlementPos.x-directions[i].x, settlementPos.y-directions[i].y);
        if (CanAttackThisTile(testTile=&home->GetLand(pos)))
        {
            Attack(&testTile->GetOwner());
            break;
        }
    }

}

void Team::SetCapital(Settlement* tile)
{
    capitalTile = tile;
}

Team::Team(unsigned int id,float damage,float reproRate,sf::Color colour)
{
    teamID = id;
    attackDamage=damage;
    reproductionRate=reproRate;
    teamColour = colour;
}


void Team::DrawCapital() const
{

        if (capitalTile!=nullptr)
        {
            capitalTile->GetHome().DrawTile(capitalColour);
        }

}



void Settlement::Simulate()
{
    ManageReproduction();
    AttackState();

}

