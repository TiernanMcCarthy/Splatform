//
// Created by tiernux on 25/02/2026.
//

#ifndef SPLATFORM_TESTCOLLECTABLE_H
#define SPLATFORM_TESTCOLLECTABLE_H
#include "AABB.h"
#include "BoxRenderer.h"
#include "Objects/Behaviour.h"

class TestPlayer;
class TestCollectable : public Behaviour
{
public:


    void Start() override;

    void Update(float deltaTime) override;

    virtual void Collect();

private:

    TestPlayer* player=nullptr;

    AABB* collider=nullptr;

    BoxRenderer* renderer;



};

#endif // SPLATFORM_TESTCOLLECTABLE_H
