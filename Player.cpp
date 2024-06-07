#include "Player.h"
#include "Rigidbody.h"

#include <iostream>
#include <stdlib.h>
#include <list>

using namespace std;

void Player::Draw()
{
    auto it = rbList.begin();
    auto& obj = *it;

    if (obj.useGravity)
    {
        obj.ApplyGravity(MathUtil::Subtract(screenHeight, position.y));
    }
    
    NormalMovement(inputValue);

    BounceAgainstWalls();
    ApplyVector(obj.velocity);
}








