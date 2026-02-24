//
// Created by tiernan on 12/25/25.
//

#ifndef SPLATFORM_AABB_H
#define SPLATFORM_AABB_H
#include "Collider.h"
#include "SFML/System/Vector2.hpp"

#endif //SPLATFORM_AABB_H

class AABB : public Collider
{
    public:

    bool transformBasedSize=true;


    AABB();

    AABB(sf::Vector2f halfSize);

    sf::Vector2f GetHalfSize();

    void SetHalfSize(sf::Vector2f halfSize);

    HitResult IntersectPoint(sf::Vector2f point);

    HitResult IntersectSegment(sf::Vector2f pos,sf::Vector2f delta, float paddingX=0, float paddingY=0);

    HitResult IntersectAABB(AABB *target);

    SweepResult SweepAABB(AABB *target, sf::Vector2f delta);

private:
    sf::Vector2f m_halfSize;

    REFLECT_BEGIN(AABB,Collider)

    REFLECT_END()

};