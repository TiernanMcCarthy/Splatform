//
// Created by Tiern on 18/02/2026.
//

#ifndef SPLATFORM_TESTPLAYER_H
#define SPLATFORM_TESTPLAYER_H
#include "Objects/Behaviour.h"

class AABB;
class TestPlayer : public Behaviour
{

    public:



    private:

    AABB* collider=nullptr;

    float moveSpeed =30;

    float jumpForce=20;
};

#endif // SPLATFORM_TESTPLAYER_H
