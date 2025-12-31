//
// Created by tiernan on 12/25/25.
//
#include "AABB.h"

#include <cmath>
#include <stdlib.h>     /* abs */

#include "Objects/GameObject.h"


AABB::AABB()
{
    halfSize=sf::Vector2f(0,0);
}

AABB::AABB(sf::Vector2f half)
{
    halfSize=half;
}


///Tests a point against this collider's position
HitResult AABB::IntersectPoint(sf::Vector2f point)
{
    HitResult result = HitResult();

    result.debugHit=false;

    sf::Vector2f gameObjectPos=gameObject->transform.GetPosition(); //Get collider position relative to gameObject

    //Compare X axis for any overlap
    float deltaX=point.x-gameObjectPos.x;
    float px = halfSize.x-abs(deltaX);

    //Test for overlap on X Axis, if none, there's no collision
    if (px<=0)
    {
        return result;
    }

    //Test again for overlap on Y
    float deltaY = point.y-gameObjectPos.y;

    float py = halfSize.y-abs(deltaY);

    if (py<=0)
    {
        return result;
    }

    //Check for the smallest overlap and create an intersection point on that edge
    if (px<py)
    {
        float sx = std::copysign(1.0f, deltaX);


        result.delta.x=px*sx;
        result.normal.x=sx;

        result.hitPosition.x=gameObjectPos.x+(halfSize.x*sx);

        result.hitPosition.y=point.y;
        result.debugHit=true;
    }
    else
    {
        float sy = std::copysign(1.0f, deltaY);
        result.delta.y=py*sy;
        result.normal.y=sy;

        result.hitPosition.x=point.x;
        result.hitPosition.y=gameObjectPos.y+(halfSize.y*sy);
        result.debugHit=true;

    }

    return result;
}

///Solves for t(Time) where intersection on a segment occurs with a box
///Will return null if there is no intersection, with time being the point of intersection
HitResult AABB::IntersectSegment(sf::Vector2f pos, sf::Vector2f delta, int paddingX, int paddingY)
{
    HitResult result;

    //Calculate linear time of intersection with box's near and far edges
    float scaleX=1.0f/delta.x;
    float scaleY=1.0f/delta.y;

    float signX=std::copysign(1.0f, scaleX);
    float signY=std::copysign(1.0f, scaleY);

    sf::Vector2f gameObjectPos=gameObject->transform.GetPosition(); //Get collider position relative to gameObject

    float nearTimeX= (gameObjectPos.x-signX*(halfSize.x+paddingX)-gameObjectPos.x)*scaleX;
    float nearTimeY= (gameObjectPos.y-signY*(halfSize.y+paddingY)-gameObjectPos.y)*scaleY;

    float farTimeX= (gameObjectPos.x+signX*(halfSize.x+paddingX)-gameObjectPos.x)*scaleX;
    float farTimeY= (gameObjectPos.y+signY*(halfSize.y+paddingY)-gameObjectPos.y)*scaleY;

    //Compare these times to see if a collision is possible
    if (nearTimeX>farTimeY || nearTimeY>farTimeX)
    {
        return result; //No collision has happened
    }

    float nearTime=nearTimeX>nearTimeY?nearTimeX:nearTimeY;
    float farTime=farTimeX<farTimeY?farTimeX:farTimeY;

    //If near time is greater or equal to 1, the line starts in front of the nearest edge and passes it
    //If the far time is less than or equal to 0, the line starts in front of the far side of the box and misses (no collision)

    if (nearTime>=1 || farTime<=0)
    {
        return result; //no collision
    }

    //We have a collision, work it out

    result.hitTime=std::clamp(nearTime,0.0f,1.0f); //The collision can only take place from 0-1 for the segment length

    //Set normal to be the inverse of the line?
    if (nearTimeX>nearTimeY)
    {
        result.normal.x= -signX;
        result.normal.y= 0;
    }
    else
    {
        result.normal.x=0;
        result.normal.y=-signY;
    }

    result.delta.x=(1.0f-result.hitTime)* -delta.x;
    result.delta.y=(1.0f-result.hitTime)* -delta.y;

    result.hitPosition.x=pos.x+delta.x*result.hitTime;
    result.hitPosition.y=pos.y+delta.y*result.hitTime;

    return result;
}
