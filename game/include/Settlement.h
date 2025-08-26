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

    bool IsAlive() const;

    static std::array<sf::Vector2i,4> directions;

    private:



    //Attributes
    float health;
    float reproductionValue;
    bool isAlive=false;

    //References

    SettlerManager* settlementManager;
    TerrainTile* home;
    Team* team;


    void ManageReproduction();

    void Reproduce();


    void ResetSettlement();
};