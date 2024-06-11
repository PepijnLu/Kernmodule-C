#include "MathUtil.h"
#include "Rigidbody.h"

#include <iostream>
#include <stdlib.h>
#include <SFML/Graphics.hpp>


using namespace std;

float mass;
MathUtil::Vector2 gravity;
MathUtil::Vector2 velocity;
MathUtil::Vector2 deltaVelocity;
sf::CircleShape obj;
float gravConstant;

Rigidbody::Rigidbody(float newMass, float newElasticity, float newMaxSpeedX, float newMaxSpeedY)
{
    this->mass = newMass;
    this->velocity.x = 0;
    this->velocity.y = 0;
    this->elasticity = newElasticity;
    this->gravity.x = 0;

    //Earth gravity
    this->gravity.y = 9.81;

    this->maxSpeedX = newMaxSpeedX;
    this->maxSpeedY = newMaxSpeedY;
}

MathUtil::Vector2 Rigidbody::ApplyForceOverTime(MathUtil::Vector2 force)
{
    MathUtil::Vector2 acceleration;

    //a = F/m
    acceleration.x = MathUtil::Divide(force.x, mass);
    acceleration.y = MathUtil::Divide(force.y, mass);

    //Make sure it doesn't go over max speed
    if (this->velocity.x < MathUtil::Abs(this->maxSpeedX))
    {
        this->velocity.x += acceleration.x * this->timeStep;
    }
    if (this->velocity.x > MathUtil::Abs(this->maxSpeedX))
    {
        this->velocity.x = this->maxSpeedX;
    }
    if (this->velocity.y < MathUtil::Abs(this->maxSpeedY))
    {
        this->velocity.y += acceleration.y * this->timeStep;
    }
    if (this->velocity.y > MathUtil::Abs(this->maxSpeedY))
    {
        this->velocity.y = this->maxSpeedY;
    }

    return velocity;
}

MathUtil::Vector2 Rigidbody::ApplyGravity(float distance)
{
    MathUtil::Vector2 gravForce;

    gravForce.x = 0;

    //Math for calculating gravitational force
    float distanceSquared = MathUtil::Pow(distance, 2);
    float massesMultiplied = MathUtil::Multiply(mass, earthMass);
    float massesOverDistanceSquared = MathUtil::Divide(massesMultiplied, distanceSquared);
    gravForce.y = MathUtil::Multiply(gravConstant, massesOverDistanceSquared);

    ApplyForceOverTime(gravForce);
    

    return gravForce;
}

//For bouncing against walls
MathUtil::Vector2 Rigidbody::AddImpulseForce()
{
    this->velocity.x = MathUtil::Multiply(-this->elasticity, this->velocity.x);

    return velocity;
}
















