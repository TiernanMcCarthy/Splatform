//
// Created by tiernan on 7/20/25.
//
#include "SettlerManager.h"
#include "Settlement.h"
#include "TerrainTile.h"
#include "WorldMap.h"

#include "GameSettings.h"

#include "Systems/ThreadPool.h"

#include <atomic>
#include <iostream>
#include <random>
//Shuffle Attack and growth directions for randomisation
static std::random_device rd;
static std::mt19937 g(rd()); // Mersenne Twister engine
void EpicFunction(std::atomic<bool>& testBool,std::atomic<bool>& testy)
{
    testBool.exchange(!testBool);
    testy.exchange(!testy);
}

SettlerManager::SettlerManager(WorldMap *map)
{

    if (map == nullptr)
    {
        std::cout<<"World map is not initialised, please review"<<std::endl;
        return;
    }
    worldMap = map;

}

/*Shuffled Indicies
std::vector<int> shuffledIndices(settlements.size());
std::iota(shuffledIndices.begin(), shuffledIndices.end(), 0);
std::shuffle(shuffledIndices.begin(), shuffledIndices.end(), g);
for (int idx : shuffledIndices) {
Settlement* s = settlements[idx];
// Do randomized processing
}
*/
void SettlerManager::StartGame(int teams)
{

    std::cout<<"Starting game with teams: "<<teams<<std::endl;

    Team* deadTeam = new Team(-1,1,1,sf::Color::Black);

    for (int i=0;i<worldMap->GetTileCount(); i++)
    {
        TerrainTile* tempTile=worldMap->GetTile(worldMap->ConvertIndexToCoordinates(i));

        if (tempTile->IsLand())
        {
            Settlement* newSettler = new Settlement(tempTile,deadTeam,this);
            settlements.push_back(newSettler);
            tempTile->DrawTile(tempTile->GetOriginalColour());
            //CreateSettler(tempTile,deadTeam);
        }
    }

    //std::shuffle(settlements.begin(), settlements.end(), g);


    for (int i=0; i<teams; i++)
    {
        Team* testTeam = new Team(i,1,1,playerColours[i]);
        TerrainTile* temp=worldMap->GetRandomTileThreaded();


        if (temp == nullptr)
        {
            std::cout<<"No terrain tile found at startup"<<std::endl;
            return;
        }
        testTeam->SetCapital(&temp->GetOwner());
        teamHolder.push_back(testTeam);

        CreateSettler(temp,testTeam);
    }

}

void SettlerManager::PushSettler(Settlement *settler)
{
    settlements.push_back(settler);
    //settler->Init();
}

uint32_t lcg_rand(uint32_t *state)
{
    uint64_t product = (uint64_t)*state * 279470273u;
    uint32_t x;

    // Not required because 5 * 279470273 = 0x5349e3c5 fits in 32 bits.
    // product = (product & 0xffffffff) + 5 * (product >> 32);
    // A multiplier larger than 0x33333333 = 858,993,459 would need it.

    // The multiply result fits into 32 bits, but the sum might be 33 bits.
    product = (product & 0xffffffff) + 5 * (uint32_t)(product >> 32);

    product += 4;
    // This sum is guaranteed to be 32 bits.
    x = (uint32_t)product + 5 * (uint32_t)(product >> 32);
    return *state = x - 4;
}

void SettlerManager::IterateSettlements()
{



    std::shuffle(Settlement::directions.begin(), Settlement::directions.end(), g);


    //Manage Team Manpower

    for (int t=0; t<teamHolder.size(); t++)
    {

        if (!teamHolder[t]->GetCapitalTile()->IsAlive()) //The capital is dead, find a new one
        {
            int teamID=teamHolder[t]->GetTeamID();

            Settlement* newCapital=nullptr;

            for (int c = 0; c < settlements.size(); c++ )
            {
                if (settlements[c]->IsAlive() && settlements[c]->GetTeamID()==teamID)
                {
                    newCapital=settlements[c];
                }
            }

            if (newCapital==nullptr)
            {
                //Team is dead
                std::cout<<"No capital settlement found"<<std::endl;
            }
        }
        teamHolder[t]->DrawCapital();
        teamHolder[t]->CalculateManpower();
    }


    //Run through settler list and complete their actions
    for (int i=0; i<settlements.size(); i++)
    {
        currentIteration = settlements[i];
        if (currentIteration->IsAlive())
        {
            currentIteration->Simulate();
        }
    }
}


void SettlerManager::CreateSettler(TerrainTile *target,Team* team)
{
    //Activate associated Settler with Tile
    Settlement* temp =&target->GetOwner();

    temp->MakeActive(team);
}
