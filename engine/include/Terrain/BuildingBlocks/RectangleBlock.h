//
// Created by Tiern on 19/02/2026.
//

#ifndef SPLATFORM_RECTANGLEBLOCK_H
#define SPLATFORM_RECTANGLEBLOCK_H
#include "Objects/Behaviour.h"

class BoxRenderer;
class AABB;
class RectangleBlock : public Behaviour
{

public:

    void Start() override;

    void Update(float deltaTime) override;

    void Awake() override;

    BoxRenderer* renderer;

    AABB* collider;



    REFLECT_BEGIN(RectangleBlock,Behaviour)



    REFLECT_END()


};



#endif // SPLATFORM_RECTANGLEBLOCK_H
