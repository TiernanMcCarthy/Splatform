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
    sf::Vector2f halfSize;

    AABB();

    AABB(sf::Vector2f halfSize);

    HitResult IntersectPoint(sf::Vector2f point);

    HitResult IntersectSegment(sf::Vector2f pos,sf::Vector2f delta, int paddingX=0, int paddingY=0);

};