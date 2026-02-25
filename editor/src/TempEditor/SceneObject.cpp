//
// Created by tiernan on 2/25/26.
//
#include "TempEditor/SceneObject.h"

#include <Objects/GameObject.h>
#include <Terrain/BuildingBlocks/RectangleBlock.h>


void SceneObject::Init(std::string filePath)
{
    path = filePath;
    objectname=path;
    size_t cutoff=objectname.find('.');
    objectname.erase(cutoff);

    renderer= gameObject->AddBehaviour<BoxRenderer>();

    gameObject->transform.localScale=sf::Vector2f(64,64);

    renderer->ApplyImage(filePath);

    renderer->drawLayer=DrawMode::UI;

    renderer->depth=55;

    selectionButton= gameObject->AddBehaviour<Button>();

    //selectionButton->OnPress.Subscribe()

    gameObject->serialise=false;
}

GameObject& SceneObject::CreateObject(sf::Vector2i pos)
{


    RectangleBlock* prefab = (new GameObject(objectname))->AddBehaviour<RectangleBlock>();

    prefab->gameObject->transform.SetPosition(sf::Vector2f(pos.x,pos.y));
    prefab->gameObject->transform.localScale=sf::Vector2f(64,64);

    return *prefab->gameObject;

}
