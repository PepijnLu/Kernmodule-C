#pragma once
#include "MathUtil.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

using namespace std;


class Rigidbody
{
    private:
    
    public:
        Rigidbody(){}
        ~Rigidbody(){}
        Rigidbody(float mass, float newElasticity, float newMaxSpeedX, float newMaxSpeedY);
        float mass;
        float maxSpeedX, maxSpeedY;
        float deltaTime;

        // 1/60th of a second (60fps)
        float timeStep = 0.016;
        
        float elasticity;
        bool useGravity;
           
        //Universal gravitational constant
        float gravConstant = MathUtil::Multiply(6.67430, (MathUtil::Pow(10, -11)));
        //Mass of the earth
        float earthMass = MathUtil::Multiply(5.9722, (MathUtil::Pow(10, 24)));

        MathUtil::Vector2 gravity;
        MathUtil::Vector2 velocity;
        MathUtil::Vector2 ApplyForceOverTime(MathUtil::Vector2 force);
        MathUtil::Vector2 ApplyGravity(float distance);
        MathUtil::Vector2 AddImpulseForce();
};