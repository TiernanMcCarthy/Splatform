//
// Created by tiernan on 2/25/26.
//

#ifndef SPLATFORM_SCENEOBJECT_H
#define SPLATFORM_SCENEOBJECT_H

#include <BoxRenderer.h>
#include <Objects/Behaviour.h>
#include <UI/Button.h>

///Editor Only hack for just creating preview of specific objects for placing, will rework for real editor later
class SceneObject : public Behaviour
{
    public:

    void Init(std::string filePath);

    std::string path;

    std::string objectname;

    BoxRenderer* renderer;

    Button* selectionButton;



    GameObject& CreateObject(sf::Vector2i pos);
};


#endif //SPLATFORM_SCENEOBJECT_H