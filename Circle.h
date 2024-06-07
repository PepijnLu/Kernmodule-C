#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Rigidbody.h"
#include "GameObject.h"

class Circle : public GameObject
{
    private:

    public:
        MathUtil::Vector2 position;

        Circle();
        Circle(int xPos, int yPos, int circleRadius, float xSpeed, int screenWidth, int screenHeight, float mass, float elasticity)
        : GameObject(xPos, yPos, circleRadius, xSpeed, screenWidth, screenHeight, mass, elasticity)
        {
            //ENEMY SPECIFIC
            std::random_device rd;  // Obtain a random number from hardware
            std::mt19937 gen(rd()); // Seed the generator
            std::uniform_int_distribution<> distrib(0, 1); // Define the range (0 or 1)

            bool randomBool = distrib(gen); // Generate the random bool

            if (randomBool)
            {
                this->xSpeed *= -1;
            }

            this->rbList.front().elasticity = elasticity;
            this->rbList.front().useGravity = true;
            this->needsRemoving = false;     
            this->player = false;
            this->shape.setFillColor(sf::Color::Red);
            //ENEMY SPECIFIC END
        }
};