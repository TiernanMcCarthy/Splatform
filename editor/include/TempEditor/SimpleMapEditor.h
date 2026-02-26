//
// Created by Tiern on 19/02/2026.
//

#ifndef SPLATFORM_SIMPLEMAPEDITOR_H
#define SPLATFORM_SIMPLEMAPEDITOR_H
#include "Objects/Behaviour.h"
#include "Terrain/BuildingBlocks/RectangleBlock.h"
#include "TestPlayer/PlayerSpawn.h"

#include "SceneObject.h"
#include "TerrainTile.h"
#include "UI/TextBox.h"

#include <map>

class ButtonFunctionality;
class EditorTempCamera;
class SceneCamera;
class TestPlayer;

inline int tileSize=64;

struct Vector2iComparator {
    bool operator()(const sf::Vector2i& lhs, const sf::Vector2i& rhs) const {
        if (lhs.x != rhs.x) return lhs.x < rhs.x;
        return lhs.y < rhs.y;
    }
};



/// Temporary measure to just draw rectangular geometry for making "levels" and saving them to disk
class SimpleMapEditor : public Behaviour {
public:


    static SimpleMapEditor* instance;

    void Update(float deltaTime) override;

    void Start() override;

    void SelectTerrainObject(SceneObject* prefab);

    void DeleteObject();


private:

    int posX=0;
    int posY=0;

    float snapSize[4] = {2,1,0.5f,0.25f};

    int currentSnap=1;

    bool tryCreate=false;

    std::map<sf::Vector2i, GameObject*, Vector2iComparator> tileMap;

    //UI
    ButtonFunctionality* editorButtons= nullptr;

    TextBox* selectedObject = nullptr;

    TextBox* coordinates = nullptr;

    std::vector<GameObject*> prefabSpacer;

    //

    SceneObject* selectedPrefab=nullptr;

    RectangleBlock* lastObject= nullptr;

    RectangleBlock* currentContext= nullptr;

    PlayerSpawn* spawnPoint= nullptr;

    TestPlayer* player = nullptr;

    EditorTempCamera* camera= nullptr;

    sf::Vector2f spawnPos;

    GameObject* selection = nullptr;

    std::vector<GameObject*> tiles;

    bool isCreating=false;

    //std::vector<>

    void SortPrefabs();

    void LoadTerrainFromFile();

    void ManageInput();

    void ManageSelection();

    void ManageSaving();

    void ManageCreation();

    void CheckStates();

    void CreateBlock();



};

#endif // SPLATFORM_SIMPLEMAPEDITOR_H
