//
// Created by tiernan on 7/14/25.
//
#pragma once
#ifndef SETTLEMENT_H
#define SETTLEMENT_H
#include "SettlerManager.h"

#endif //SETTLEMENT_H

#include <SFML/Graphics.hpp>

class TerrainTile;

class SettlerManager;

struct Team
{
private:
    unsigned int teamID;

    float attackDamage;

    float reproductionRate;

    int landCount=0;

    sf::Color teamColour;

public:

    Team(unsigned int id,float damage=1,float reproRate=1,sf::Color colour=sf::Color::Black)
    {
        teamID = id;
        attackDamage=damage;
        reproductionRate=reproRate;
        teamColour = colour;
    }

    float GetReproductionRate() const
    {
        return reproductionRate;
    }

    sf::Color GetTeamColour() const
    {
        return teamColour;
    }

    unsigned int GetTeamID() const
    {
        return teamID;
    }

    int GetlandCount() const
    {
        return landCount;
    }

    void AddLand()
    {
        landCount++;
    }

    void RemoveLand()
    {
        landCount--;
    }

};

class Settlement
{
    public:


    Settlement(TerrainTile* newHome,Team* newTeam, SettlerManager* parent);

    ~Settlement();

    TerrainTile& GetHome();

    void Simulate();

    void Init();

    void ResetReproduction();

    void MakeActive(Team* newTeam);

    void Kill();

    void ReceiveDamage(float damage);

    bool IsAlive() const;

    static std::array<sf::Vector2i,4> directions;

    int GetTeamID();


    private:



    //Attributes
    float health =100;
    float attack =10;
    float reproductionValue;
    bool isAlive=false;

    //References

    SettlerManager* settlementManager;
    TerrainTile* home;
    Team* team;


    void ManageReproduction();

    void Reproduce();

    void ResetSettlement();

    bool CanAttackThisTile(TerrainTile* testTile);

    void Attack(Settlement* target);

    void AttackState();
};