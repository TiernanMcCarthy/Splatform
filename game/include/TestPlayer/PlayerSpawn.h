//
// Created by Tiern on 19/02/2026.
//

#ifndef SPLATFORM_PLAYERSPAWN_H
#define SPLATFORM_PLAYERSPAWN_H
#include "Objects/Behaviour.h"
class PlayerSpawn : public Behaviour
{
    public:

    void Start() override;


    REFLECT_BEGIN(PlayerSpawn,Behaviour)


    REFLECT_END()


};

#endif // SPLATFORM_PLAYERSPAWN_H
