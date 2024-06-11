#include "Player.h"
#include "Rigidbody.h"

#include <iostream>
#include <stdlib.h>
#include <list>

using namespace std;

void Player::Draw()
{
    if (rbList.front()->useGravity)
    {
        rbList.front()->ApplyGravity(MathUtil::Subtract(screenHeight, position.y));
    }
    
    NormalMovement(inputValue);

    BounceAgainstWalls();
    ApplyVector(rbList.front()->velocity);
}








