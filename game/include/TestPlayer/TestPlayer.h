//
// Created by Tiern on 18/02/2026.
//

#ifndef SPLATFORM_TESTPLAYER_H
#define SPLATFORM_TESTPLAYER_H
#include <vector>

#include "Objects/Behaviour.h"

class RectangleBlock;
class AABB;
class TestPlayer : public Behaviour
{

    public:

    void Start() override;

    void Update(float deltaTime) override;

    REFLECT_BEGIN(TestPlayer, Behaviour)


    REFLECT_END()



    private:

    AABB* collider=nullptr;

    float moveSpeed =30;

    float jumpForce=20;

    std::vector<RectangleBlock*> blocks;
};

#endif // SPLATFORM_TESTPLAYER_H
