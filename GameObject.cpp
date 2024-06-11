#include "GameObject.h"
#include "Rigidbody.h"

#include <iostream>
#include <stdlib.h>
#include <list>
#include <SFML/Graphics.hpp>

using namespace std;

GameObject::GameObject(int xPos, int yPos, int circleRadius, float xSpeed, int screenWidth, int screenHeight, float mass, float elasticity)
{
    this->position.x = xPos;
    this->position.y = yPos;
    this->circleRadius = circleRadius;
    this->circleDiameter = circleRadius * 2;
    this->xSpeed = xSpeed;
    this->maxSpeed = 5;
    this->stdVec.x = 1;
    this->stdVec.y = 0;
    this->inCollision = false;

    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    
    sf::CircleShape shape(circleRadius);
    this->shape = shape;
    this->shape.setPosition(position.x, position.y);

    this->needsRemoving = false;
    this->hitThePlayer = false;
    this->awardPoint = true;
    rbList.push_back(std::make_unique<Rigidbody>(mass, elasticity, 8, 10));
    //Rigidbody rb = Rigidbody(mass, elasticity, 8, 10);
    //rbList.insert(std::next(rbList.begin()), rb);
}

void GameObject::Draw()
{   
    rbList.front()->ApplyGravity(MathUtil::Subtract(screenHeight, position.y));
    NormalMovement(stdVec);
    
    BounceAgainstWalls();
    //cout << "Velocity: " << rbList.front()->velocity.x << " " << rbList.front()->velocity.y << endl;
    ApplyVector(rbList.front()->velocity);
    //delete *it;
}

void GameObject::BounceAgainstWalls()
{ 
    if ((position.x <= 0) && !inCollision) 
    {    
        rbList.front()->AddImpulseForce();
        inCollision = true;
        if (!player)
        {
            xSpeed *= -1;
        }
    }
    else if (((position.x + circleDiameter) >= screenWidth) && !inCollision) 
    {   
        rbList.front()->AddImpulseForce();
        inCollision = true;
        if (!player)
        {
            xSpeed *= -1;
        }
    }
    else if ((position.x >= 5) && ((position.x + circleDiameter) <= screenWidth - 5))
    {
        inCollision = false;
    }
    if (!player)
    {
        if(position.y >= screenHeight)
        {
            this->needsRemoving = true;
        }
    }   
}

void GameObject::NormalMovement(MathUtil::Vector2 vec)
{
    if (inCollision)
    {
        vec.x = 0;
    }
    else
    {
        vec.x = MathUtil::Multiply(vec.x, xSpeed);
    }
    rbList.front()->ApplyForceOverTime(vec);
}


void GameObject::ApplyVector(MathUtil::Vector2 vec)
{
    //Prevent glitching out the screen partially
    if ((position.x - vec.x < 0))
    {
        if (position.x >= 0)
        {
            vec.x += position.x;
        }
        else
        {
            vec.x += MathUtil::Add(MathUtil::Abs(position.x), MathUtil::Abs(vec.x));
        }
    }
    else if ((position.x + circleDiameter + vec.x > screenWidth))
    {
        if (position.x + circleDiameter <= screenWidth)
        {
            vec.x += (position.x + circleDiameter - screenWidth);
        }
        else
        {
            vec.x -= MathUtil::Add(MathUtil::Abs((position.x + circleDiameter - screenWidth)), MathUtil::Abs(vec.x));
        }
    }

    //Move
    position.x = MathUtil::Add(position.x, vec.x);
    position.y = MathUtil::Add(position.y, vec.y);

    this->shape.setPosition(position.x, position.y);
    this->centerPointX = MathUtil::Add(position.x, circleRadius);
    this->centerPointY = MathUtil::Add(position.y, circleRadius);
}








