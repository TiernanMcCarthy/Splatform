//
// Created by tiernan on 7/18/25.
//

#pragma once
#include <vector>

class Settlement;
class WorldMap;
class SettlerManager
{
public:

    SettlerManager(WorldMap* map);

    ~SettlerManager() = default;

    void StartGame(int teams=2);
private:

    std::vector<Settlement*> settlements;

    WorldMap* worldMap;
};