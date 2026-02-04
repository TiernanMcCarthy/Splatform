//
// Created by tiernux on 27/12/2025.
//

#ifndef SPLATFORM_COLLIDERDEBUG_H
#define SPLATFORM_COLLIDERDEBUG_H
#include "Objects/Behaviour.h"

#endif //SPLATFORM_COLLIDERDEBUG_H


class AABBTestClass;
class BoxRenderer;
class AABB;

class ColliderDebug :public Behaviour
{
public:

    void Start() override;
    void Update(float deltaTime) override;
    void OnDestroy() override;

    AABB* ourCollider;

    BoxRenderer* renderer;

    BoxRenderer* collisionDot;


    //Test Boxes
    AABBTestClass* boxVbox;

    float moveSpeed=250;


    REFLECT_BEGIN(ColliderDebug, Behaviour)
    REFLECT_VAR(moveSpeed)
    REFLECT_END()

};
