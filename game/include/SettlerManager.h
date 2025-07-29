//
// Created by tiernan on 7/18/25.
//

#pragma once
#include <vector>

class Settlement;
class WorldMap;
class ThreadPool;
class SettlerManager
{
public:

    SettlerManager(WorldMap* map);

    ~SettlerManager() = default;

    void StartGame(int teams=2);

    void IterateSettlements();

    void PushSettler(Settlement* settler);
private:

    std::vector<Settlement*> settlements;

    ThreadPool* threadPool;

    WorldMap* worldMap;
};