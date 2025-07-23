//
// Created by tiernan on 7/14/25.
//
#pragma once
#ifndef SETTLEMENT_H
#define SETTLEMENT_H

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


    Settlement(TerrainTile* newHome,Team* newTeam);

    ~Settlement();

    TerrainTile& GetHome();

    void Simulate(SettlerManager* manager);

    void Init();

    private:

    void ManageReproduction(SettlerManager* manager);

    void Reproduce(SettlerManager* manager);

    TerrainTile* home;

    Team* team;

    float reproductionValue;
};