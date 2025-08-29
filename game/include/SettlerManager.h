//
// Created by tiernan on 7/18/25.
//

#pragma once
#include <vector>

struct Team;
class Settlement;
class WorldMap;
class ThreadPool;
class TerrainTile;

class SettlerManager
{
public:

    SettlerManager(WorldMap* map);

    ~SettlerManager() = default;

    void StartGame(int teams=2);

    void IterateSettlements();

    void PushSettler(Settlement* settler);

    void CreateSettler(TerrainTile* target,Team* team);
private:

    std::vector<Team*> teamHolder;

    std::vector<Settlement*> settlements;

    ThreadPool* threadPool;

    WorldMap* worldMap;

    Settlement* currentIteration;
};