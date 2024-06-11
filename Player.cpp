#include "Player.h"
#include "Rigidbody.h"

#include <iostream>
#include <stdlib.h>
#include <list>

using namespace std;

void Player::Draw()
{
    if (rb->useGravity)
    {
        rb->ApplyGravity(MathUtil::Subtract(screenHeight, position.y));
    }

    //Move with the player inputs    
    NormalMovement(inputValue);

    //Handle bouncing against walls
    BounceAgainstWalls();

    //Apply the rigidbody's vector
    ApplyVector(rb->velocity);
}








