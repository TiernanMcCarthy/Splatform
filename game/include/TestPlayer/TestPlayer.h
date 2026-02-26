//
// Created by Tiern on 18/02/2026.
//

#ifndef SPLATFORM_TESTPLAYER_H
#define SPLATFORM_TESTPLAYER_H
#include <vector>

#include "Objects/Behaviour.h"

class BoxRenderer;
class RectangleBlock;
class AABB;
class TestPlayer : public Behaviour
{

    public:

    void Start() override;

    void Update(float deltaTime) override;

    int GetScore() const {return score;}

    void AddScore(int scoreValue);

    REFLECT_BEGIN(TestPlayer, Behaviour)


    REFLECT_END()

    //would move to private, but current collision simple is inadequate
    AABB* collider=nullptr;

    private:

    int score=0;

    float horizontalInput;
    sf::Vector2f velocity=sf::Vector2f(0,0);

    BoxRenderer* renderer =nullptr;



    float groundDrag=0.98f;

    float gravityForce=-9.81f;

    float acceleration =15;

    float maxSpeed=180;

    float jumpForce=600;

    bool tryJump=false;
    bool isGrounded=false;

    std::vector<RectangleBlock*> blocks;

    void TestCollision();

    void HandleInput();

    void CheckJump(float deltaTime);

    void ManageDrag();

    void ManageMovement(float deltaTime);

    void ApplyGravity(float deltaTime);
};

#endif // SPLATFORM_TESTPLAYER_H
