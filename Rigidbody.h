#pragma once
#include "MathUtil.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;


class Rigidbody
{
    private:
    
    public:
        Rigidbody()
        {
            cout << "" << endl;
        };
        Rigidbody(float mass, float newElasticity, float newMaxSpeedX, float newMaxSpeedY);
        float mass;
        float maxSpeedX, maxSpeedY;
        float deltaTime;
        float timeStep = 0.02;
        float elasticity;
        bool useGravity;
        float gravConstant;
        float earthMass;
        MathUtil::Vector2 gravity;
        MathUtil::Vector2 velocity;
        MathUtil::Vector2 ApplyForceOverTime(MathUtil::Vector2 force);
        MathUtil::Vector2 ApplyGravity(float distance);
        MathUtil::Vector2 AddImpulseForce();
};