//
// Created by tiernux on 04/02/2026.
//

#ifndef SPLATFORM_SCENELOADDUMMY_H
#define SPLATFORM_SCENELOADDUMMY_H
#include "../../engine/include/Objects/Behaviour.h"

#include <iostream>

class SceneLoadDummy : public Behaviour
{

    public:

    float testValue=5;

    void Start() override;

    void Update(float deltaTime) override;


    void Serialize(Serializer& s) override {
        std::string oldCtx = s.currentContext;
        s.currentContext = "SceneLoadDummy" + std::to_string(ObjectID);
        s.Property("ObjectID", ObjectID);

        // Debug Print
        if (s.mode == Mode::Saving) {
            std::cout << "SAVING | Addr: " << this << " | ID: " << ObjectID << " | Val: " << testValue << std::endl;
        }

        s.Property("testValue", testValue);
        s.currentContext = oldCtx;
    }
};

#endif // SPLATFORM_SCENELOADDUMMY_H
