//
// Created by tiernux on 01/01/2026.
//

#ifndef SPLATFORM_AABBTESTCLASS_H
#define SPLATFORM_AABBTESTCLASS_H
#include "Systems/Core.h"
#include "CollisionTests.h"
#include "Objects/GameObject.h"

#endif //SPLATFORM_AABBTESTCLASS_H


class AABB;
class BoxRenderer;

class AABBTestClass : public Behaviour
{
    public:

    void Start() override;


    AABB* collider;

    BoxRenderer* renderer;

    REFLECT_BEGIN(AABBTestClass,Behaviour)


    REFLECT_END()
};
