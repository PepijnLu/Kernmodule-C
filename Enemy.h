#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Rigidbody.h"
#include "GameObject.h"

class Enemy : public GameObject
{
    private:

    public:
        MathUtil::Vector2 position;

        Enemy(){};
        ~Enemy(){};
        Enemy(int xPos, int yPos, int circleRadius, float xSpeed, int screenWidth, int screenHeight, float mass, float elasticity, float maxSpeedX, float maxSpeedY)
        : GameObject(xPos, yPos, circleRadius, xSpeed, screenWidth, screenHeight, mass, elasticity, maxSpeedX, maxSpeedY)
        {
            std::random_device rd;  // Obtain a random number from hardware
            std::mt19937 gen(rd()); // Seed the generator
            std::uniform_int_distribution<> distrib(0, 1); // Define the range (0 or 1)

            bool randomBool = distrib(gen); //Generate the random bool

            if (randomBool)
            {
                this->xSpeed = MathUtil::Multiply(this->xSpeed, -1);
            }

            this->rb->elasticity = elasticity;
            this->rb->useGravity = true;
            this->needsRemoving = false;     
            this->player = false;
            this->shape.setFillColor(sf::Color::Red);
        }
};